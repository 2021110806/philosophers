/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:10:41 by minjeon2          #+#    #+#             */
/*   Updated: 2023/11/19 22:06:26 by minjeon2         ###   ########.fr       */
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
