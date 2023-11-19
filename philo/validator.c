/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:04:49 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 20:46:37 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_args_validate(t_philo_info *philo_info)
{
	if (!(philo_info -> time_to_die >= 0 && philo_info -> time_to_eat >= 0 && \
	philo_info->time_to_sleep && philo_info-> \
	times_each_philosopher_must_eat >= -1 && \
	philo_info -> number_of_philosophers > 0))
	{
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
