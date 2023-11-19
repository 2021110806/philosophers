/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:48 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 22:12:42 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_data	*initialize_data(t_data *data, t_philo_info *philos_info, \
pthread_mutex_t *fork_mutex, pthread_mutex_t *printf_mutex)
{
	data = malloc (sizeof (t_data));
	if (!data)
		return (NULL);
	data -> philo_info = philos_info;
	data -> philos = philos_info -> philos;
	data -> printf_mutex = printf_mutex;
	data -> fork_mutex = fork_mutex;
	return (data);
}

void	start_philos_threads(t_philo_info *philos_info, \
pthread_mutex_t *fork_mutex, pthread_mutex_t *printf_mutex)
{
	struct timeval			time;
	pthread_t				*threads;
	int						i;
	t_data					*data;

	i = 0;
	threads = malloc(sizeof (pthread_t) * philos_info->number_of_philosophers);
	if (!threads)
		return ;
	gettimeofday(&time, 0);
	while (i < philos_info -> number_of_philosophers)
	{
		data = initialize_data(data, philos_info, fork_mutex, printf_mutex);
		if (!data)
			return ;
		data -> philos[i].birth_time = get_time_in_milliseconds(&time);
		data -> philos[i].last_eating = get_time_in_milliseconds(&time);
		data -> id = i;
		pthread_create(&threads[i], 0, cycle, data);
		i++;
	}
	data = initialize_data(data, philos_info, fork_mutex, printf_mutex);
	if (!data)
		return ;
	start_monitoring_thread(data, threads);
}

int	main(int argc, char **argv)
{
	t_philo_info	*philo_info;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	died_philos_mutex;
	pthread_mutex_t	printf_mutex;

	philo_info = parse_argv(argc, argv);
	if (!philo_info || !is_args_validate(philo_info))
		return (1);
	philo_info -> eating_mutex = &eating_mutex;
	philo_info -> died_philo_mutex = &died_philos_mutex;
	philo_info -> fork = malloc (sizeof(int) * \
	philo_info->number_of_philosophers);
	if (!philo_info -> fork)
		return (1);
	pthread_mutex_init((philo_info -> eating_mutex), 0);
	pthread_mutex_init(philo_info -> died_philo_mutex, 0);
	pthread_mutex_init(&printf_mutex, 0);
	philo_info -> philos = make_philos_list(philo_info);
	fork_mutex = make_forks(philo_info);
	if (!fork_mutex || !philo_info -> philos)
		return (1);
	start_philos_threads(philo_info, fork_mutex, &printf_mutex);
	free_ptr(philo_info -> philos, philo_info);
	return (0);
}
