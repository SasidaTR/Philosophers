#include "../include/include.h"

void	check_death(t_philosopher *philo)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (timestamp - philo->last_meal_time > philo->arguments->time_to_die)
	{
		pthread_mutex_lock(&philo->arguments->simulation_mutex);
		if (philo->arguments->simulation_running)
		{
			print_status(philo, "died");
			philo->arguments->simulation_running = 0;
		}
		pthread_mutex_unlock(&philo->arguments->simulation_mutex);
	}
}

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philosopher *philo)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	print_status(philo, "is eating");
	philo->last_meal_time = timestamp;
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->arguments->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->arguments->done_eating_mutex);
		philo->arguments->philosophers_done_eating++;
		pthread_mutex_unlock(&philo->arguments->done_eating_mutex);
	}
	usleep(philo->arguments->time_to_eat * 1000);
}

void	sleep_and_think(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->arguments->time_to_sleep * 1000);
	print_status(philo, "is thinking");
}
