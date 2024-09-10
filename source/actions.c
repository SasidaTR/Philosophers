#include "../include/include.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		printf("%ld %d is thinking\n", current_timestamp(), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", current_timestamp(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", current_timestamp(), philo->id);
		philo->last_meal = current_timestamp();
		printf("%ld %d is eating\n", current_timestamp(), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%ld %d is sleeping\n", current_timestamp(), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->times_must_eat != -1 && philo->meals_eaten >= philo->data->times_must_eat)
			break ;
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;
	int	finished;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
		i++;
	}
	finished = 0;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (current_timestamp() - data->philosophers[i].last_meal > data->time_to_die)
			{
				printf("%ld %d died\n", current_timestamp(), data->philosophers[i].id);
				return ;
			}
			i++;
		}
		i = 0;
		finished = 1;
		if (data->times_must_eat != -1)
		{
			while (i < data->number_of_philosophers)
			{
				if (data->philosophers[i].meals_eaten < data->times_must_eat)
				{
					finished = 0;
					break ;
				}
				i++;
			}
			if (finished)
				break ;
		}
		usleep(100);
	}
}
