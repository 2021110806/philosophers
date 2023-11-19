/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:02:19 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 20:02:21 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philosopher philo, pthread_mutex_t *printf_mutex, \
struct timeval time)
{
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d died\n", get_time_in_milliseconds(&time) - \
	philo.birth_time, philo.id);
	pthread_mutex_unlock(printf_mutex);
	return ;
}
