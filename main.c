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
		check_if_philosopher_starve(data -> philo, data -> philo_info, data -> printf_mutex);
		take_a_left_fork(data -> philo, data -> fork, data -> printf_mutex);
		check_if_philosopher_starve(data -> philo, data -> philo_info, data -> printf_mutex);
		take_a_right_fork(data -> philo, data -> fork, data -> printf_mutex);
		check_if_philosopher_starve(data -> philo, data -> philo_info, data -> printf_mutex);
		eat(data -> philo, data -> philo_info, data -> fork, data -> printf_mutex);
		think(data -> philo, data -> printf_mutex);
		ft_sleep(data -> philo, data -> philo_info, data -> printf_mutex);
	}
	return (0);
}

void	check_if_philosopher_starve(t_philosopher *philo, t_philo_info *philo_info, pthread_mutex_t *printf_mutex)
{
	struct timeval time;

	gettimeofday(&time, 0);
	if ((int) (time.tv_usec * 0.001 + time.tv_sec * 1000) - philo -> last_eating > philo_info ->number_of_times_each_philosopher_must_eat)
		die(philo, printf_mutex);
}

 int	main(int argc, char **argv)
 {
	t_philosopher	**philos;
	t_philo_info	*philo_info;
	t_philosopher	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printf_mutex;
	pthread_t		*threads;
	t_data			*data;
	int				*threadIDs;
	void *(*fptr) (void *);
	int				i;

	argc  = argc + 1;
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
	pthread_mutex_init(&printf_mutex, 0);
	i = 0;
	while (i < philo_info -> number_of_philosophers)
	{
		philo = malloc (sizeof(t_philosopher));
		philo -> id = i;
		philo -> left_fork = i;
		philo -> right_fork = (philo_info -> number_of_philosophers) - 1 - i;
		philo -> number_of_eating = 0;
		philos[i] = philo;
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
		data -> philo -> last_eating = 0;
		pthread_create(&threads[i], 0, fptr, data);
		i++;
	}

	i = 0;
	while(i < philo_info -> number_of_philosophers)
	{
		pthread_join(threads[i], 0);
		i++;
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

	스레드의 대기 시간을 추적하는 변수를 사용합니다.
해당 스레드에서 뮤텍스를 잠금(lock)하기 전에 시간을 기록합니다.
뮤텍스 잠금에 성공하면, 대기 시간을 다시 계산하여 현재 시간과의 차이를 계산합니다.
만약 대기 시간이 설정한 임계값을 초과하면 원하는 메시지를 출력합니다.
뮤텍스를 잠금 해제(unlock)하기 전에 대기 시간 추적 변수를 초기화합니다.

	
	*/
	return (0);
 }