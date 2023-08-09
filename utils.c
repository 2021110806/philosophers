#include "philo.h"

// void eat(t_philosopher *philo, t_philo_info *philo_info)
// {
// 	struct timeval time;

// 	gettimeofday(&time, 0);
// 	ft_printf("%d %d is eating", time.tv_sec, philo -> id);
// 	usleep(philo_info -> time_to_eat * 1000000);
// }

void ft_sleep(t_philosopher *philo, t_philo_info *philo_info)
{
	struct timeval time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is sleeping", time.tv_sec, philo -> id);
	usleep(philo_info -> time_to_sleep * 1000000);
}

void think(t_philosopher *philo)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is thinking", time.tv_sec, philo -> id);
}

void take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is taken a fork", time.tv_sec, philo -> id);
	pthread_mutex_lock(&fork[philo -> left_fork]);
	ft_printf("%d %d is eating", time.tv_sec, philo -> id);
}

void take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is taken a fork", time.tv_sec, philo -> id);
	pthread_mutex_lock(&fork[philo -> right_fork]);
}

void eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork)
{
	struct timeval time;

	pthread_mutex_unlock(&fork[philo -> left_fork]);
	pthread_mutex_unlock(&fork[philo -> right_fork]);
	ft_printf("%d %d is eating", time.tv_sec, philo -> id);
	usleep(philo_info -> time_to_eat * 1000000);
	philo -> number_of_eating++;
}

void die(t_philosopher *philo)
{
	struct timeval time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is dead", time.tv_sec, philo -> id);
}
