/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:06:16 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/18 21:20:28 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_data *data, t_philo_info *philo_info, \
pthread_mutex_t *printf_mutex)
{
	struct timeval	time;
	int				i;

	i = 0;
	pthread_mutex_lock(printf_mutex);
	gettimeofday(&time, 0);
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(printf_mutex);
		return (0);
	}
	printf("%lld %d is sleeping\n", get_time_in_milliseconds(&time) - \
	data -> philos[data -> id].birth_time, data -> id);
	pthread_mutex_unlock(printf_mutex);
	wait_for_sleeping_or_eating(philo_info, &time, 1);
	usleep(200);
	return (1);
}

int	think(t_data *data, t_philo_info *philo_info, \
pthread_mutex_t *printf_mutex)
{
	struct timeval	time;

	pthread_mutex_lock(printf_mutex);
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(printf_mutex);
		return (0);
	}
	gettimeofday(&time, 0);
	printf("%lld %d is thinking\n", get_time_in_milliseconds(&time) - \
	data -> philos[data -> id].birth_time,data ->id);
	pthread_mutex_unlock(printf_mutex);
	usleep((philo_info->time_to_die - (philo_info -> time_to_sleep + philo_info -> time_to_eat)) / 2);
	return (1);
}

int	take_a_left_fork(t_data *data, pthread_mutex_t *fork_mutex, \
pthread_mutex_t *printf_mutex, t_philo_info *philo_info)
{
	struct timeval	time;

	pthread_mutex_lock(&fork_mutex[data -> philos[data -> id].left_fork]);
	philo_info -> fork[data -> philos[data -> id].left_fork] = true;
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
	philo_info -> fork[data -> philos[data -> id].left_fork] = true;
	gettimeofday(&time, 0);
	if (philo_info -> died_philo || philo_info -> all_full)
	{
		pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].right_fork]);
		return (0);
	}
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d has taken a fork\n", get_time_in_milliseconds(&time) \
	- data -> philos[data -> id].birth_time, data -> id);
	pthread_mutex_unlock(printf_mutex);
	return (1);
}

int	eat(t_data *data, t_philo_info *philo_info, pthread_mutex_t *fork_mutex, pthread_mutex_t *printf_mutex)
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
		pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].left_fork]);
		pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].right_fork]);
		return (0);
	}
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is eating\n", get_time_in_milliseconds(&time) - \
	data -> philos[data -> id].birth_time, data -> philos[data -> id].id);
	pthread_mutex_unlock(printf_mutex);
	wait_for_sleeping_or_eating(philo_info, &time, 0);
	philo_info -> fork[data -> philos[data -> id].left_fork] = false;
	philo_info -> fork[data -> philos[data -> id].left_fork] = false;
	pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].left_fork]);
	pthread_mutex_unlock(&fork_mutex[data -> philos[data -> id].right_fork]);
	data -> philos[data -> id].number_of_eating++;
	return (1);
}
