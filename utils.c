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
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is sleeping\n", get_time_in_milliseconds(time), philo -> id);
	usleep(philo_info -> time_to_sleep * 1000);
	pthread_mutex_unlock(printf_mutex);
}

void	think(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is thinking\n", get_time_in_milliseconds(time), philo -> id);
	pthread_mutex_unlock(printf_mutex);
}

void	take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(&fork[philo -> left_fork]);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is taken a left fork\n",get_time_in_milliseconds(time), philo -> id);
	
	pthread_mutex_unlock(printf_mutex);
}

void	take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(&fork[philo -> right_fork]);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is taken a right fork\n", get_time_in_milliseconds(time), philo -> id);
	pthread_mutex_unlock(printf_mutex);
}

void	eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval *time;

	pthread_mutex_lock(printf_mutex);
	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	philo -> last_eating =  get_time_in_milliseconds(time);
	printf("%lld %d is eating\n", philo -> last_eating, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	usleep(philo_info -> time_to_eat * 1000);
	pthread_mutex_unlock(&fork[philo -> left_fork]);
	pthread_mutex_unlock(&fork[philo -> right_fork]);
	philo -> number_of_eating++;
}

void	die(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval *time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	printf("%lld %d is dead\n", get_time_in_milliseconds(time), philo -> id);
	exit(0);
}

long long	get_time_in_milliseconds(struct timeval *time)
{
	return (long long)(time->tv_sec * 1000) + (time->tv_usec / 1000);
}
