/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:48 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/18 21:11:25 by minjeon2         ###   ########.fr       */
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

void	*cycle(void *inp)
{
	t_data	*data;

	data = (t_data *) inp;
	if (data -> philo_info -> number_of_philosophers % 2 == 0)
		wait_threads(data);
	while (1)
	{
		pthread_mutex_lock(data -> philo_info -> died_philo_mutex);
		if (data -> philo_info -> died_philo)
		{
			pthread_mutex_unlock(data -> philo_info -> died_philo_mutex);
			return (free_data(data));
		}
		pthread_mutex_unlock(data -> philo_info -> died_philo_mutex);
		if (!take_fork(data))
			return (free_data(data));
		if (is_philosopher_full(data -> philos[data -> id], data -> philo_info))
			return (free_data(data));
		if (!ft_sleep(data, data -> philo_info, data -> printf_mutex))
			return (free_data(data));
		if (!think(data, data -> philo_info, data -> printf_mutex))
			return (free_data(data));
	}
	free(data);
	return (0);
}

void	start_philos_threads(t_philo_info *philos_info, pthread_mutex_t *fork_mutex)
{
	t_data				*data;
	struct timeval		time;
	pthread_t			*threads;
	int					i;
	pthread_mutex_t			printf_mutex;

	i = 0;
	threads = malloc (sizeof (pthread_t) * \
	philos_info -> number_of_philosophers);
	while (i < philos_info -> number_of_philosophers)
	{
		data = malloc (sizeof (t_data));
		data -> philo_info = philos_info;
		data -> philos = philos_info -> philos;
		data -> printf_mutex = &printf_mutex;
		data -> fork_mutex = fork_mutex;
		gettimeofday(&time, 0);
		data -> philos[i].birth_time = get_time_in_milliseconds(&time);
		data -> philos[i].last_eating = get_time_in_milliseconds(&time);
		data -> id = i;
		pthread_create(&threads[i], 0, cycle, data);
		i++;
	}
	data -> philos = philos_info -> philos;
	start_monitoring_thread(data, threads);
}

int	main(int argc, char **argv)
{
	t_philo_info	*philo_info;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	died_philos_mutex;

	if (!(argc == 5 || argc == 6))
		return (1);
	philo_info = parse_argv(argc, argv);
	if (!philo_info || !is_args_validate(philo_info))
		return (1);
	philo_info -> eating_mutex = &eating_mutex;
	philo_info -> died_philo_mutex = &died_philos_mutex;
	philo_info -> died_philo = 0;
	philo_info -> all_full = 0;
	philo_info -> fork = malloc (sizeof (int) * philo_info -> number_of_philosophers);
	ft_memset(philo_info -> fork, true, sizeof(philo_info));
	pthread_mutex_init((philo_info -> eating_mutex), 0);
	pthread_mutex_init(philo_info -> died_philo_mutex, 0);
	philo_info -> philos = make_philos_list(philo_info);
	fork_mutex = make_forks(philo_info);
	if (!fork_mutex)
		return (0);	
	start_philos_threads(philo_info, fork_mutex);
	free_ptr(philo_info -> philos, philo_info);
	return (0);
}