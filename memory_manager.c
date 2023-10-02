/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:56:28 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/02 22:44:55 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ptr(t_philosopher **philos, t_philo_info *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		free(philos[i]);
		i++;
	}
	free(philo_info -> fork_lock);
	free(philos);
	free(philo_info);
}

int	ft_strlen(char *s)
{
	int	return_value;

	return_value = 0;
	while (*s)
	{
			return_value++;
			s++;
	}
	return (return_value);
}

int	is_args_validate(t_philo_info *philo_info)
{
	if (!(philo_info -> time_to_die >= 0 && philo_info -> time_to_eat >= 0 && \
	philo_info -> time_to_sleep && philo_info -> \
	number_of_times_each_philosopher_must_eat >= 0 && \
	philo_info -> number_of_philosophers > 0))
	{
		free(philo_info -> fork_lock);
		free(philo_info);
		return (0);
	}
	return (1);
}

int	is_argv_validate(t_philo_info *philo_info)
{
	if (!(philo_info -> time_to_die >= 0 && philo_info -> time_to_eat >= 0 \
	&& philo_info -> time_to_sleep >= 0 && \
	philo_info -> number_of_philosophers > 0))
	{
		free(philo_info);
		return (0);
	}
	return (1);
}

int	is_overflow_longlong(char **argv, t_philo_info *philo_info)
{
	if (ft_strlen(argv[1]) > 10 || \
	ft_strlen(argv[2]) > 10 || \
	ft_strlen(argv[3]) > 10 \
	|| ft_strlen(argv[4]) > 10)
	{
		free(philo_info);
		return (1);
	}
	return (0);
}
