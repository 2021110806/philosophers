/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:19:14 by minjeon2          #+#    #+#             */
/*   Updated: 2023/08/18 20:30:05 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philosopher_full(t_philosopher *philo, t_philo_info *philo_info)
{
	if (philo ->number_of_eating < philo_info -> \
	number_of_times_each_philosopher_must_eat)
		return (0);
	return (1);
}

int	is_all_philosophers_full(t_philosopher **philos, t_philo_info *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		if (is_philosopher_full(philos[i], philo_info))
			return (0);
		i++;
	}
	return (1);
}

int	check_if_philosopher_starve(t_philosopher *philo, \
t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;
	long long		curr_time;

	gettimeofday(&time, 0);
	curr_time = get_time_in_milliseconds(&time);
	pthread_mutex_lock((philo_info -> eating_mutex));
	if (curr_time - philo -> last_eating >= philo_info -> time_to_die)
	{
		philo_info -> died_philo = 1;
		die(philo, printf_mutex);
		pthread_mutex_unlock((philo_info -> eating_mutex));
		return (1);
	}
	pthread_mutex_unlock((philo_info -> eating_mutex));
	return (0);
}

void	*monitoring_if_there_is_starve_philosopher(void *inp)
{
	int					i;
	t_data				*data;

	i = 0;
	data = (t_data *) inp;
	while (1)
	{
		if (i >= data -> philo_info -> number_of_philosophers)
			i = 0;
		if (check_if_philosopher_starve(data -> philos[i], \
		data -> philo_info, data -> printf_mutex))
			return (0);
		i++;
	}
}

void	start_monitoring_thread(t_data *data, pthread_t *threads)
{
	int				i;
	pthread_t		*monitoring;

	monitoring = malloc (sizeof (pthread_t *));
	pthread_create(monitoring, 0, \
	monitoring_if_there_is_starve_philosopher, data);
	i = 0;
	while (i < data -> philo_info -> number_of_philosophers)
	{
		pthread_join(threads[i], 0);
		pthread_join(*monitoring, 0);
		i++;
	}
	free(monitoring);
	free(threads);
}
