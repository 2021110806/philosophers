/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:52:24 by minjeon2          #+#    #+#             */
/*   Updated: 2023/10/02 22:39:25 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philosopher {
	int			id;
	int			left_fork;
	int			right_fork;
	int			number_of_eating;
	long long	last_eating;
	long long	birth_time;
}	t_philosopher;

typedef struct s_philo_info {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				*fork_lock;
	int				died_philo;
	int				all_full;
	t_philosopher	**philos;
	pthread_mutex_t	*died_philo_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*eating_mutex;
}	t_philo_info;

typedef struct s_data {
	t_philosopher	*philo;
	t_philosopher	**philos;
	t_philo_info	*philo_info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*printf_mutex;
	int				is_free;
}	t_data;

int				ft_sleep(t_philosopher *philo, t_philo_info *philo_info, \
pthread_mutex_t *printf_mutex);
int				think(t_philosopher *philo, t_philo_info *philo_info, \
pthread_mutex_t *printf_mutex);
int				take_a_left_fork(t_philosopher *philo, pthread_mutex_t *fork, \
pthread_mutex_t *printf_mutex, t_philo_info *philo_info);
int				take_a_right_fork(t_philosopher *philo, pthread_mutex_t *fork, \
pthread_mutex_t *printf_mutex, t_philo_info *philo_info);
int				eat(t_philosopher *philo, t_philo_info *philo_info, \
pthread_mutex_t *fork, pthread_mutex_t *printf_mutex);
void			die(t_philosopher *philo, pthread_mutex_t *printf_mutex, \
struct timeval time);
int				check_if_philosopher_starve(t_philosopher *philo, \
t_philo_info *philo_info, pthread_mutex_t *printf_mutex);
long long		get_time_in_milliseconds(struct timeval *time);
void			wait_for_sleeping_or_eating(t_philo_info *philo_info, \
struct timeval *start_time, int is_sleep);
t_philo_info	*parse_argv(int argc, char **argv);
void			start_monitoring_thread(t_data	*data, pthread_t *threads);
t_philo_info	*parse_argv(int argc, char **argv);
void			start_monitoring_thread(t_data *data, pthread_t *threads);
void			*monitoring_if_there_is_starve_philosopher(void *inp);
int				is_philosopher_full(t_philosopher *philo, \
t_philo_info *philo_info);
int				is_all_philosophers_full(t_philosopher **philos, \
t_philo_info *philo_info);
t_philosopher	**make_philos_list(t_philo_info *philo_info);
pthread_mutex_t	*make_forks(t_philo_info *philo_info);
void			lock_or_unlock_forklock(t_data *data, int will_lock);
long long		ft_atoi(const char *str);
void			free_ptr(t_philosopher **philos, \
t_philo_info *philo_info);
int				ft_strlen(char *s);
int				is_args_validate(t_philo_info *philo_info);
int				is_overflow_longlong(char **argv, t_philo_info *philo_info);
int				is_argv_validate(t_philo_info *philo_info);
void			wait_threads(t_data *data);
void			*free_data(t_data *data);
#endif
