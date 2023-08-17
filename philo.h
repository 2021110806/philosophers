#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct s_philosopher {
	int		id;
	int		left_fork;
	int		right_fork;
	int		number_of_eating;
	long long	last_eating;
	long long	birth_time;
}	t_philosopher;

typedef struct s_philo_info {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	*fork_lock;
}	t_philo_info;

typedef struct s_data {
	t_philosopher *philo;
	t_philosopher	**philos;
	t_philo_info *philo_info;
	pthread_mutex_t *fork;
	pthread_mutex_t *printf_mutex;
}	t_data;

void		ft_sleep(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex);
void		think(t_philosopher *philo, pthread_mutex_t *printf_mutex);
void	take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork, t_philo_info *philo_info, pthread_mutex_t *printf_mutex);
void	take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork, t_philo_info *philo_info, pthread_mutex_t *printf_mutex);
void		eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork, pthread_mutex_t *printf_mutex);
void		die(t_philosopher *philo, pthread_mutex_t *printf_mutex);
void		check_if_philosopher_starve(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex);
long long	get_time_in_milliseconds(struct timeval *time);
void		wait_for_sleeping_or_eating(t_philo_info *philo_info, t_philosopher *philo, struct timeval *start_time, int is_sleep);
#endif