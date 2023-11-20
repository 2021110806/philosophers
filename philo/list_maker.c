/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:23 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/20 18:31:37 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

t_philo_info	*parse_argv(int argc, char **argv)
{
	t_philo_info	*philo_info;

	if (!(argc == 5 || argc == 6))
		return (0);
	philo_info = malloc (sizeof(t_philo_info));
	ft_memset(philo_info, 0, sizeof(t_philo_info));
	if (is_overflow_longlong(argv, philo_info))
		return (0);
	philo_info -> number_of_philosophers = ft_atoi(argv[1]);
	philo_info -> time_to_die = ft_atoi(argv[2]);
	philo_info -> time_to_eat = ft_atoi(argv[3]);
	philo_info -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_strlen(argv[5]) > 10)
			return (0);
		philo_info->times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (philo_info -> times_each_philosopher_must_eat < 0)
			return (free_philo_info(philo_info));
	}
	else
		philo_info -> times_each_philosopher_must_eat = -1;
	if (!is_argv_validate(philo_info))
		return (0);
	return (philo_info);
}

pthread_mutex_t	*make_forks(t_philo_info *philo_info)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc (sizeof (pthread_mutex_t) * \
	philo_info -> number_of_philosophers);
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		pthread_mutex_init(&fork[i], 0);
		i++;
	}
	return (fork);
}

t_philosopher	*make_philos_list(t_philo_info *philo_info)
{
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = malloc (sizeof (t_philosopher) * \
	philo_info -> number_of_philosophers);
	if (!philos)
		return (0);
	while (i < philo_info -> number_of_philosophers)
	{
		philos[i].id = i;
		philos[i].left_fork = i;
		if (i == philo_info -> number_of_philosophers - 1)
			philos[i].right_fork = 0;
		else
			philos[i].right_fork = i + 1;
		philos[i].number_of_eating = 0;
		i++;
	}
	return (philos);
}
