/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:10:41 by minjeon2          #+#    #+#             */
/*   Updated: 2023/08/18 16:34:19 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is dead\n", get_time_in_milliseconds(time) - \
	philo -> birth_time, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	exit(0);
}

long long	get_time_in_milliseconds(struct timeval *time)
{
	return ((long long)(time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	wait_for_sleeping_or_eating(t_philo_info *philo_info, \
struct timeval *start_time, int is_sleep)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	while (1)
	{
		gettimeofday(time, 0);
		if (get_time_in_milliseconds(time) - \
		get_time_in_milliseconds(start_time) >= \
		philo_info -> time_to_sleep && is_sleep)
			break ;
		if (get_time_in_milliseconds(time) - \
		get_time_in_milliseconds(start_time) >= \
		philo_info -> time_to_eat && !is_sleep)
			break ;
		usleep(5);
	}
}

t_philo_info	*parse_argv(int argc, char **argv)
{
	t_philo_info	*philo_info;

	philo_info = malloc (sizeof(t_philo_info));
	philo_info -> number_of_philosophers = ft_atoi(argv[1]);
	philo_info -> time_to_die = ft_atoi(argv[2]);
	philo_info -> time_to_eat = ft_atoi(argv[3]);
	philo_info -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_info -> \
		number_of_times_each_philosopher_must_eat = (int) ft_atoi(argv[5]);
	else
		philo_info -> number_of_times_each_philosopher_must_eat = 2147483647;
	philo_info -> fork_lock = \
	malloc (sizeof(int) * philo_info -> number_of_philosophers);
	return (philo_info);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	return_value;

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
	return (return_value);
}
