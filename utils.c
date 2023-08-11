#include "philo.h"

// void eat(t_philosopher *philo, t_philo_info *philo_info)
// {
// 	struct timeval time;

// 	gettimeofday(&time, 0);
// 	ft_printf("%d %d is eating", time.tv_sec, philo -> id);
// 	usleep(philo_info -> time_to_eat * 1000000);
// }

void	ft_sleep(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	pthread_mutex_lock(printf_mutex);
	ft_printf("%d %d is sleeping\n", time.tv_usec * 0.001 + time.tv_sec * 1000 , philo -> id);
	pthread_mutex_unlock(printf_mutex);
	usleep(philo_info -> time_to_sleep * 1000000);
}

void	think(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	pthread_mutex_lock(printf_mutex);
	ft_printf("%d %d is thinking\n", time.tv_usec * 0.001 + time.tv_sec * 1000, philo -> id);
	pthread_mutex_unlock(printf_mutex);
}

void	take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	pthread_mutex_lock(printf_mutex);
	ft_printf("%d %d is taken a fork\n",time.tv_usec * 0.001 + time.tv_sec * 1000, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	pthread_mutex_lock(&fork[philo -> left_fork]);
}

void	take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	pthread_mutex_lock(printf_mutex);
	ft_printf("%d %d is taken a fork\n", time.tv_usec * 0.001 + time.tv_sec * 1000, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	pthread_mutex_lock(&fork[philo -> right_fork]);
}

void	eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval time;

	pthread_mutex_lock(printf_mutex);
	ft_printf("%d %d is eating\n", time.tv_usec * 0.001 + time.tv_sec * 1000, philo -> id);
	philo -> last_eating =  time.tv_usec * 0.001 + time.tv_sec * 1000;
	pthread_mutex_unlock(printf_mutex);
	usleep(philo_info -> time_to_eat * 1000000);
	pthread_mutex_unlock(&fork[philo -> left_fork]);
	pthread_mutex_unlock(&fork[philo -> right_fork]);
	philo -> number_of_eating++;
}

void	die(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval time;

	gettimeofday(&time, 0);
	ft_printf("%d %d is dead\n", time.tv_usec * 0.001 + time.tv_sec * 1000, philo -> id);
	exit(0);
}
