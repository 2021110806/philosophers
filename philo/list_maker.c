/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:23 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/18 20:49:26 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

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
