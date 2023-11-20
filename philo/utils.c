/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:10:41 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/20 18:32:16 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_milliseconds(struct timeval *time)
{
	return ((long long)(time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	wait_threads(t_data *data)
{
	if (data -> id % 2 == 0)
		usleep(1000);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*return_value;

	return_value = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		return_value[i] = (unsigned char) c;
		i++;
	}
	return ((void *) return_value);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			minus;
	long long	return_value;

	i = 0;
	minus = 1;
	return_value = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		return_value = return_value * 10 + minus * (str[i] - 48);
		i++;
	}
	if (return_value > 2147483647)
		return_value = -1;
	return ((int) return_value);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*return_value;
	unsigned long	i;

	i = 0;
	return_value = (char *) malloc (sizeof (char) * count * size);
	if (!return_value)
		return ((void *)0);
	while (i < count * size)
		return_value[i++] = 0;
	return ((void *)return_value);
}
