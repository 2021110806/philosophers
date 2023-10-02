/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:48 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/02 22:41:56 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_or_unlock_forklock(t_data *data, int will_lock)
{
	pthread_mutex_lock(data -> philo_info -> fork_mutex);
	if (will_lock)
	{
		data -> philo_info -> fork_lock[data -> philo -> left_fork] = 1;
		data -> philo_info -> fork_lock[data -> philo ->right_fork] = 1;
	}
	else
	{
		data -> philo_info -> fork_lock[data -> philo -> left_fork] = 0;
		data -> philo_info -> fork_lock[data -> philo -> right_fork] = 0;
	}
	pthread_mutex_unlock(data -> philo_info -> fork_mutex);
	return ;
}

int	take_fork(t_data *data)
{
	if (data -> philo -> id % 2 == 1)
	{
		if (!take_a_left_fork(data -> philo, data->fork, \
		data->printf_mutex, data -> philo_info))
			return (0);
		if (!take_a_right_fork(data->philo, data->fork, \
		data->printf_mutex, data -> philo_info))
			return (0);
	}
	else
	{
		if (!take_a_right_fork(data->philo, data->fork, \
		data->printf_mutex, data -> philo_info))
			return (0);
		if (!take_a_left_fork(data->philo, data->fork, \
		data->printf_mutex, data -> philo_info))
			return (0);
	}
	if (!eat(data ->philo, data->philo_info, data->fork, data->printf_mutex))
		return (0);
	return (1);
}

void	*cycle(void *inp)
{
	t_data	*data;

	data = (t_data *) inp;
	wait_threads(data);
	while (1)
	{
		pthread_mutex_lock(data -> philo_info -> died_philo_mutex);
		if (data -> philo_info -> died_philo)
		{
			pthread_mutex_unlock(data -> philo_info -> died_philo_mutex);
			return (0);
		}
		pthread_mutex_unlock(data -> philo_info -> died_philo_mutex);
		if (!take_fork(data))
			return (0);
		if (is_philosopher_full(data -> philo, data -> philo_info))
			return (free_data(data));
		if (!ft_sleep(data -> philo, data -> philo_info, data -> printf_mutex))
			return (0);
		if (!think(data -> philo, data -> philo_info, data -> printf_mutex))
			return (0);
	}
	free(data);
	return (0);
}

void	start_philo_threads(t_philo_info *philo_info, pthread_mutex_t *fork)
{
	t_data				*data;
	struct timeval		time;
	pthread_t			*threads;
	pthread_mutex_t		printf_mutex;
	int					i;

	i = 0;
	threads = malloc (sizeof (pthread_t) * \
	philo_info -> number_of_philosophers);
	while (i < philo_info -> number_of_philosophers)
	{
		data = malloc (sizeof (t_data));
		data -> philo = philo_info -> philos[i];
		data -> philo_info = philo_info;
		data -> printf_mutex = &printf_mutex;
		data -> fork = fork;
		gettimeofday(&time, 0);
		data -> philo -> birth_time = get_time_in_milliseconds(&time);
		data -> philo -> last_eating = get_time_in_milliseconds(&time);
		pthread_create(&threads[i], 0, cycle, data);
		i++;
	}
	data -> philos = philo_info -> philos;
	start_monitoring_thread(data, threads);
}

void a(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_philo_info	*philo_info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	died_philo_mutex;

	atexit(a);
	if (!(argc == 5 || argc == 6))
		return (1);
	philo_info = parse_argv(argc, argv);
	if (!philo_info || !is_args_validate(philo_info))
		return (1);
	philo_info -> fork_mutex = &fork_mutex;
	philo_info -> eating_mutex = &eating_mutex;
	philo_info -> died_philo_mutex = &died_philo_mutex;
	philo_info -> died_philo = 0;
	philo_info -> all_full = 0;
	pthread_mutex_init((philo_info -> fork_mutex), 0);
	pthread_mutex_init((philo_info -> eating_mutex), 0);
	pthread_mutex_init(philo_info -> died_philo_mutex, 0);
	philo_info -> philos = make_philos_list(philo_info);
	fork = make_forks(philo_info);
	start_philo_threads(philo_info, fork);
	free(fork);
	free_ptr(philo_info -> philos, philo_info);
	return (0);
}
