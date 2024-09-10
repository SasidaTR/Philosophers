#include "../include/include.h"

long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->philosophers || !data->forks)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		data->philosophers[i].last_meal = current_timestamp();
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->philosophers);
	free(data->forks);
}
