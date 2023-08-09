#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "./libft/libft.h"

typedef struct s_philosopher {
	int	id;
	int	left_fork;
	int	right_fork;
	int	number_of_eating;
}	t_philosopher;

typedef struct s_philo_info {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_info;

typedef struct s_data {
	t_philosopher *philo;
	t_philo_info *philo_info;
	pthread_mutex_t *fork;
}	t_data;

void ft_sleep(t_philosopher *philo, t_philo_info *philo_info);
void think(t_philosopher *philo);
void take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork);
void take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork);
void eat(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork);
void die(t_philosopher *philo);
#endif