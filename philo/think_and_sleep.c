/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_and_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:06:16 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 20:09:50 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_sleeping_or_eating(t_philo_info *philo_info, \
struct timeval *start_time, int is_sleep)
{
	struct timeval	time;

	while (1)
	{
		gettimeofday(&time, 0);
		if (get_time_in_milliseconds(&time) - \
		get_time_in_milliseconds(start_time) >= \
		philo_info -> time_to_sleep && is_sleep)
			break ;
		if (get_time_in_milliseconds(&time) - \
		get_time_in_milliseconds(start_time) >= \
		philo_info -> time_to_eat && !is_sleep)
			break ;
		usleep(100);
	}	
}

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
	data -> philos[data -> id].birth_time, data ->id);
	pthread_mutex_unlock(printf_mutex);
	usleep((philo_info->time_to_die - \
	(philo_info -> time_to_sleep + philo_info -> time_to_eat)) / 2);
	return (1);
}
