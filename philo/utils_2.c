/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:37:17 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/18 20:10:30 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_data *data)
{
	if (data -> id % 2 == 0)
		usleep(1000);
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
