#include "../include/include.h"

void	print_status(t_philosopher *philo, const char *status)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("[Time: %ld] Philosopher %d %s\n", timestamp, philo->id, status);
}

void	free_all(t_philosopher *philosophers, pthread_mutex_t *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	if (forks)
	{
		while (i < number_of_philosophers)
			pthread_mutex_destroy(&forks[i++]);
		free(forks);
	}
	if (philosophers)
		free(philosophers);
	pthread_mutex_destroy(&philosophers->arguments->done_eating_mutex);
	pthread_mutex_destroy(&philosophers->arguments->simulation_mutex);
}
