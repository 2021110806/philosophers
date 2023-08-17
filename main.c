#include "philo.h"

int	is_philosopher_full(t_philosopher *philo, t_philo_info *philo_info)
{
	if (philo ->number_of_eating < philo_info -> number_of_times_each_philosopher_must_eat)
		return (0);
	return (1);
}

int		is_all_philosophers_full(t_philosopher **philos, t_philo_info *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		if (is_philosopher_full(philos[i], philo_info))
			return (0); 
		i++;
	}
	return (1);
}

void	*cycle(void *inp)
{
	t_data *data;

	data = (t_data *) inp;
	while (!is_philosopher_full(data -> philo, data -> philo_info))
	{
		while (1)
		{
			if (!(data -> philo_info -> fork_lock[data -> philo -> left_fork]) && (!(data -> philo_info -> fork_lock[data -> philo -> right_fork])))
				{
					if (data -> philo -> id % 2 == 1)
					{
						data -> philo_info -> fork_lock[data -> philo -> left_fork] = 1;
						data -> philo_info -> fork_lock[data -> philo -> right_fork] = 1;
						take_a_left_fork(data -> philo, data -> fork, data -> philo_info, data -> printf_mutex);
						take_a_right_fork(data -> philo, data -> fork,  data -> philo_info, data -> printf_mutex);
					}
					else
					{
						data -> philo_info -> fork_lock[data -> philo -> right_fork] = 1;
						data -> philo_info -> fork_lock[data -> philo -> left_fork] = 1;
						take_a_right_fork(data -> philo, data -> fork, data -> philo_info, data -> printf_mutex);
						take_a_left_fork(data -> philo, data -> fork,  data -> philo_info, data -> printf_mutex);
					}
					eat(data -> philo, data -> philo_info, data -> fork, data -> printf_mutex);
					data -> philo_info -> fork_lock[data -> philo -> left_fork] = 0;
					data -> philo_info -> fork_lock[data -> philo -> right_fork] = 0;
					break;
				}
		}
		ft_sleep(data -> philo, data -> philo_info, data -> printf_mutex);
		think(data -> philo, data -> printf_mutex);
	}
	return (0);
}

void	check_if_philosopher_starve(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval 	*time;
	long long		curr_time;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, 0);
	curr_time = get_time_in_milliseconds(time);
	if (curr_time - philo -> last_eating >= philo_info -> time_to_die)
		die(philo, printf_mutex);
	// printf("curr : %lld, last eat : %lld, can wait : %lld\n", curr_time,philo -> last_eating, (long long) philo_info -> time_to_die);
	// printf("difference : %lld\n", curr_time - philo -> last_eating);
}

void	*monitoring_if_there_is_starve_philosopher(void *inp)
{
	int					i;
	t_data				*data;

	i = 0;
	data = (t_data *) inp;
	while (1)
	{
		if (i >= data -> philo_info -> number_of_philosophers)
			i = 0;
		check_if_philosopher_starve(data -> philos[i], data -> philo_info, data -> printf_mutex);
		i++;
	}
}

 int	main(int argc, char **argv)
 {
	t_philosopher	**philos;
	t_philo_info	*philo_info;
	t_philosopher	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printf_mutex;
	pthread_t		*threads;
	pthread_t		*monitoring;
	t_data			*data;
	int				*threadIDs;
	struct timeval *time;
	void *(*cycle_ptr) (void *);
	void *(*monitor_ptr) (void *);
	int					i;

	cycle_ptr = cycle;
	monitor_ptr = monitoring_if_there_is_starve_philosopher;
	time = malloc(sizeof(struct timeval));
	philo_info = malloc (sizeof(t_philo_info));
	philo_info -> number_of_philosophers = ft_atoi(argv[1]);
	philo_info -> time_to_die = ft_atoi(argv[2]);
	philo_info -> time_to_eat = ft_atoi(argv[3]);
	philo_info -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_info -> number_of_times_each_philosopher_must_eat = (int) ft_atoi(argv[5]);
	else
		philo_info -> number_of_times_each_philosopher_must_eat = 2147483647;
	philos = malloc (sizeof (t_philosopher *) * philo_info -> number_of_philosophers);
	fork = malloc (sizeof (pthread_mutex_t) * philo_info -> number_of_philosophers);
	threads = malloc (sizeof (pthread_t) * philo_info -> number_of_philosophers);
	monitoring = malloc (sizeof (pthread_t *));
	threadIDs = malloc (sizeof (int) * philo_info -> number_of_philosophers);
	philo_info -> fork_lock = malloc (sizeof(int) * philo_info -> number_of_philosophers);
	pthread_mutex_init(&printf_mutex, 0);
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		philo = malloc (sizeof(t_philosopher));
		philo -> id = i + 1;
		philo -> left_fork = i;
		philo -> right_fork = (philo_info -> number_of_philosophers - 1 != i) * (i + 1);
		philo_info -> fork_lock[i] = 0;
		philo -> number_of_eating = 0;
		philos[i] = philo;
		usleep(100);
		pthread_mutex_init(&fork[i], 0);
		i++;
	}
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		data = malloc (sizeof (t_data));
		data -> philo = philos[i];
		data -> philo_info = philo_info;
		data -> fork = fork;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		data -> printf_mutex = &printf_mutex;
		gettimeofday(time, 0);
		data -> philo -> birth_time = get_time_in_milliseconds(time);
		data -> philo -> last_eating = get_time_in_milliseconds(time);
		pthread_create(&threads[i], 0, cycle_ptr, data);
		i++;
	}
	data -> philos = philos;
	pthread_create(monitoring, 0, monitor_ptr, data);
	i = 0;
	while(i < philo_info -> number_of_philosophers)
	{
		pthread_join(threads[i], 0);
		i++;
	}
	return (0);
 }