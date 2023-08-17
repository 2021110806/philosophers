#include "philo.h"

void	ft_sleep(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;
	int				i;

	i = 0;
	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is sleeping\n",  get_time_in_milliseconds(time) - philo -> birth_time, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	wait_for_sleeping_or_eating(philo_info,  philo, time, 1);
	usleep(200);
}

void	think(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is thinking\n", get_time_in_milliseconds(time) - philo -> birth_time, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	usleep(100);
}

void	take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(&fork[philo -> left_fork]);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is taken a left fork %d\n",get_time_in_milliseconds(time) - philo -> birth_time, philo -> id, philo -> left_fork);
	pthread_mutex_unlock(printf_mutex);
}

void	take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	pthread_mutex_lock(&fork[philo -> right_fork]);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is taken a right fork %d\n", get_time_in_milliseconds(time) - philo -> birth_time, philo -> id, philo -> right_fork);
	pthread_mutex_unlock(printf_mutex);
}

void	eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex)
{
	struct timeval *time;
	int				i;

	i = 0;
	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	philo -> last_eating =  get_time_in_milliseconds(time);
	pthread_mutex_lock(printf_mutex);
	printf("%lld %d is eating\n",  get_time_in_milliseconds(time) - philo -> birth_time, philo -> id);
	pthread_mutex_unlock(printf_mutex);
	wait_for_sleeping_or_eating(philo_info, philo, time, 0);
	pthread_mutex_unlock(&fork[philo -> left_fork]);
	pthread_mutex_unlock(&fork[philo -> right_fork]);
	philo -> number_of_eating++;
}

void	die(t_philosopher *philo, pthread_mutex_t *printf_mutex)
{
	struct timeval *time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	printf("%lld %d is dead\n",  get_time_in_milliseconds(time) - philo -> birth_time, philo -> id);
	exit(0);
}

long long	get_time_in_milliseconds(struct timeval *time)
{
	return (long long)(time->tv_sec * 1000) + (time->tv_usec / 1000);
}

void	wait_for_sleeping_or_eating(t_philo_info *philo_info, t_philosopher *philo, struct timeval *start_time, int is_sleep)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	while (1)
	{
		gettimeofday(time, 0);
		if (get_time_in_milliseconds(time) - get_time_in_milliseconds(start_time) >= philo_info -> time_to_sleep && is_sleep)
			break ;
		if (get_time_in_milliseconds(time) - get_time_in_milliseconds(start_time) >= philo_info -> time_to_eat && !is_sleep)
			break ;
		usleep(5);
	}
}
