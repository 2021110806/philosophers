/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:23 by minjeon2          #+#    #+#             */
/*   Updated: 2023/08/17 20:54:02 by minjeon2         ###   ########.fr       */
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

t_philosopher	**make_philos_list(t_philo_info *philo_info)
{
	int				i;
	t_philosopher	**philos;
	t_philosopher	*philo;

	i = 0;
	philos = malloc (sizeof (t_philosopher *) * \
	philo_info -> number_of_philosophers);
	while (i < philo_info -> number_of_philosophers)
	{
		philo = malloc (sizeof(t_philosopher));
		philo -> id = i + 1;
		philo -> left_fork = i;
		if (i == philo_info -> number_of_philosophers - 1)
			philo -> right_fork = 0;
		else
			philo -> right_fork = i + 1;
		philo_info -> fork_lock[i] = 0;
		philo -> number_of_eating = 0;
		philos[i] = philo;
		i++;
	}
	return (philos);
}
