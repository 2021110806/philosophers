/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:48 by minjeon2          #+#    #+#             */
/*   Updated: 2023/08/18 20:13:00 by minjeon2         ###   ########.fr       */
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

void	take_fork(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(data -> philo_info -> fork_mutex);
		if (!(data -> philo_info -> fork_lock[data -> philo -> left_fork]) \
		&& (!(data -> philo_info -> fork_lock[data -> philo -> right_fork])))
		{
			pthread_mutex_unlock(data -> philo_info -> fork_mutex);
			if (data -> philo -> id % 2 == 1)
			{
				take_a_left_fork(data -> philo, data->fork, data->printf_mutex);
				take_a_right_fork(data->philo, data->fork, data->printf_mutex);
			}
			else
			{
				take_a_right_fork(data->philo, data->fork, data->printf_mutex);
				take_a_left_fork(data->philo, data->fork, data->printf_mutex);
			}
			eat(data ->philo, data->philo_info, data->fork, data->printf_mutex);
			lock_or_unlock_forklock(data, 0);
			break ;
		}
		pthread_mutex_unlock(data -> philo_info -> fork_mutex);
	}
}

void	*cycle(void *inp)
{
	t_data	*data;

	data = (t_data *) inp;
	while (1)
	{
		if (is_philosopher_full(data -> philo, data -> philo_info))
			return (0);
		if (data -> philo_info -> died_philo)
			return (0);
		take_fork(data);
		ft_sleep(data -> philo, data -> philo_info, data -> printf_mutex);
		think(data -> philo, data -> printf_mutex);
	}
	free(data);
	return (0);
}

void	start_philo_threads(t_philo_info *philo_info, \
t_philosopher **philos, pthread_mutex_t *fork)
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
		data -> philo = philos[i];
		data -> philo_info = philo_info;
		data -> printf_mutex = &printf_mutex;
		data -> fork = fork;
		gettimeofday(&time, 0);
		data -> philo -> birth_time = get_time_in_milliseconds(&time);
		data -> philo -> last_eating = get_time_in_milliseconds(&time);
		pthread_create(&threads[i], 0, cycle, data);
		i++;
	}
	data -> philos = philos;
	start_monitoring_thread(data, threads);
}

int	main(int argc, char **argv)
{
	t_philosopher	**philos;
	t_philo_info	*philo_info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	fork_mutex;

	if (!(argc == 5 || argc == 6))
		return (1);
	philo_info = parse_argv(argc, argv);
	if (!philo_info)
	{
		return (1);
	}
	philo_info -> fork_mutex = &fork_mutex;
	philo_info -> eating_mutex = &eating_mutex;
	philo_info -> died_philo = 0;
	pthread_mutex_init((philo_info -> fork_mutex), 0);
	pthread_mutex_init((philo_info -> eating_mutex), 0);
	philos = make_philos_list(philo_info);
	fork = make_forks(philo_info);
	start_philo_threads(philo_info, philos, fork);
	free(fork);
	free_ptr(philos, philo_info);
	return (0);
}
