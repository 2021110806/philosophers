/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:02:53 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 20:29:39 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *data)
{
	if (data -> id % 2 == 1)
	{
		if (!take_a_left_fork(data, data->fork_mutex, \
		data->printf_mutex, data -> philo_info))
			return (0);
		if (!take_a_right_fork(data, data->fork_mutex, \
		data->printf_mutex, data -> philo_info))
			return (0);
	}
	else
	{
		if (!take_a_right_fork(data, data->fork_mutex, \
		data->printf_mutex, data -> philo_info))
			return (0);
		if (!take_a_left_fork(data, data->fork_mutex, \
		data->printf_mutex, data -> philo_info))
			return (0);
	}
	if (!eat(data, data->philo_info, data->fork_mutex, data->printf_mutex))
		return (0);
	return (1);
}

int	take_a_left_fork(t_data *data, pthread_mutex_t *fork_mutex, \
pthread_mutex_t *printf_mutex, t_philo_info *philo_info)
{
	struct timeval	time;

	pthread_mutex_lock(&fork_mutex[data -> philos[data -> id].left_fork]);
	philo_info -> fork[data -> philos[data -> id].left_fork] = TRUE;
	gettimeofday(&time, 0);
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].left_fork]);
		return (0);
	}
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d has taken a fork\n", get_time_in_milliseconds(&time) \
	- data -> philos[data -> id].birth_time, data -> id);
	pthread_mutex_unlock(printf_mutex);
	return (1);
}

int	take_a_right_fork(t_data *data, pthread_mutex_t *fork_mutex, \
pthread_mutex_t *printf_mutex, t_philo_info *philo_info)
{
	struct timeval	time;

	pthread_mutex_lock(&fork_mutex[data -> philos[data -> id].right_fork]);
	philo_info -> fork[data -> philos[data -> id].left_fork] = TRUE;
	gettimeofday(&time, 0);
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(&fork_mutex[data->philos[data -> id].right_fork]);
		return (0);
	}
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d has taken a fork\n", get_time_in_milliseconds(&time) \
	- data -> philos[data -> id].birth_time, data -> id);
	pthread_mutex_unlock(printf_mutex);
	return (1);
}

int	eat(t_data *data, t_philo_info *philo_info, \
pthread_mutex_t *fork_mutex, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;
	int				i;

	i = 0;
	gettimeofday(&time, 0);
	pthread_mutex_lock((philo_info -> eating_mutex));
	data -> philos[data -> id].last_eating = get_time_in_milliseconds(&time);
	pthread_mutex_unlock((philo_info -> eating_mutex));
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(&fork_mutex[data->philos[data->id].left_fork]);
		pthread_mutex_unlock(&fork_mutex[data->philos[data->id].right_fork]);
		return (0);
	}
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is eating\n", get_time_in_milliseconds(&time) - \
	data -> philos[data -> id].birth_time, data -> philos[data -> id].id);
	pthread_mutex_unlock(printf_mutex);
	wait_for_sleeping_or_eating(philo_info, &time, 0);
	philo_info -> fork[data -> philos[data -> id].left_fork] = FALSE;
	philo_info -> fork[data -> philos[data -> id].left_fork] = FALSE;
	pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].left_fork]);
	pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].right_fork]);
	data -> philos[data -> id].number_of_eating++;
	return (1);
}
