/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:56:28 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/20 18:32:08 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ptr(t_philosopher *philos, t_philo_info *philo_info, \
pthread_mutex_t *fork_mutex)
{
	free(fork_mutex);
	free(philo_info -> fork);
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

void	*free_data(t_data *data)
{
	free(data);
	return (0);
}

void	*free_philo_info(t_philo_info *philo_info)
{
	free(philo_info);
	return (0);
}
