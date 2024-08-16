#include "../include/include.h"

void	print_status(t_philosopher *philo, const char *status)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d %s\n", timestamp, philo->id, status);
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
	usleep(philo->arguments->time_to_eat * 1000);
}

void	sleep_and_think(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->arguments->time_to_sleep * 1000);
	print_status(philo, "is thinking");
}
