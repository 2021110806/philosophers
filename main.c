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

void	cycle(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *fork)
{
	while (!is_philosopher_full(philo, philo_info))
	{
		take_a_left_fork(philo, philo_info, fork);
		take_a_right_fork(philo, philo_info, fork);
		eat(philo, philo_info, fork);
		think(philo, philo_info);
		ft_sleep(philo, philo_info);
	}
}

 int	main(int argc, char **argv)
 {
	t_philosopher	**philos;
	t_philo_info	*philo_info;
	t_philosopher	*philo;
	pthread_mutex_t	*fork;
	pthread_t		*threads;
	int				*threadIDs;
	void (*fptr) (t_philosopher *, t_philo_info *, pthread_mutex_t *);
	int				i;

	fptr = cycle;
	philo_info = malloc (sizeof(t_philo_info));
	philo_info -> number_of_philosophers = ft_atoi(argv[1]);
	philo_info -> time_to_die = ft_atoi(argv[2]);
	philo_info -> time_to_eat = ft_atoi(argv[3]);
	philo_info -> time_to_sleep = ft_atoi(argv[4]);
	philo_info -> number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	philos = malloc (sizeof (t_philosopher *) * philo_info -> number_of_philosophers);
	fork = malloc (sizeof (pthread_mutex_t *) * philo_info -> number_of_philosophers);
	threads = malloc (sizeof (pthread_t *) * philo_info -> number_of_philosophers);
	threadIDs = malloc (sizeof (int *) * philo_info -> number_of_philosophers);
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		philo = malloc (sizeof(t_philosopher));
		philo -> id = i;
		philo -> left_fork = i;
		philo -> right_fork = (philo_info -> number_of_philosophers - 1) - 1;
		philo -> number_of_eating = 0;
		philos[i] = philo;
		pthread_mutex_init(&fork[i], 0);
		free(philo);
	}
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		pthread_create(&threads[i], 0, fptr, 0);
		i++;
	}

	i = 0;
	while(i < philo_info -> number_of_philosophers)
	{
		pthread_join(threads[i], 0);
	}
	/*
	number of philosopher만큼 malloc
	philosopher 구조체 (id, left fork, right fork)
	 while(true) {
                lstick.acquire(); // 왼쪽 집어들기
                rstick.acquire(); // 오른쪽 집어들기
                eating(); // 식사
                rstick.release(); // 오른쪽 내려놓기
                lstick.release(); // 왼쪽 내려놓기
                thinking(); // 생각하기
            }
	philo 생성, fork개수만큼 mutex 생성
	각 철학자에 적용시킬 사이클 함수 생성 (먹고 자고 생각하고)
	레프트 포크 집어들면 오른쪽 포크 집어뜰들때까지 대기

	
	*/
	return (0);
 }