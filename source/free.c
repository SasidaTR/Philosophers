#include "../include/include.h"

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
}
