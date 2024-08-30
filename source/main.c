#include "../include/include.h"

void	*hunger_games(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->arguments->simulation_mutex);
		if (philo->arguments->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->arguments->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->arguments->simulation_mutex);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_and_think(philo);
		check_death(philo);
		pthread_mutex_lock(&philo->arguments->done_eating_mutex);
		if (philo->arguments->philosophers_done_eating == philo->arguments->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo->arguments->done_eating_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->arguments->done_eating_mutex);
	}
	return (NULL);
}

void	init_threads(t_arg *arguments, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < arguments->number_of_philosophers)
	{
		pthread_create(&(philosophers[i].thread), NULL, hunger_games, &(philosophers[i]));
		i++;
	}
	i = 0;
	while (i < arguments->number_of_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

int	init_philosophers(t_arg *arguments, t_philosopher **philosophers, pthread_mutex_t **forks)
{
	int	i;

	*philosophers = malloc(sizeof(t_philosopher) * arguments->number_of_philosophers);
	*forks = malloc(sizeof(pthread_mutex_t) * arguments->number_of_philosophers);
	if (!*philosophers || !*forks)
		return (1);
	i = 0;
	while (i < arguments->number_of_philosophers)
		pthread_mutex_init(&(*forks)[i++], NULL);
	i = 0;
	while (i < arguments->number_of_philosophers)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].last_meal_time = 0;
		(*philosophers)[i].meals_eaten = 0;
		(*philosophers)[i].left_fork = &(*forks)[i];
		(*philosophers)[i].right_fork = &(*forks)[(i + 1) % arguments->number_of_philosophers];
		(*philosophers)[i].arguments = arguments;
		i++;
	}
	arguments->philosophers_done_eating = 0;
	pthread_mutex_init(&arguments->done_eating_mutex, NULL);
	arguments->simulation_running = 1;
	pthread_mutex_init(&arguments->simulation_mutex, NULL);
	return (0);
}

int	check(int argc, char **argv)
{
	int		i;
	int		j;

	if (argc > 6 || argc < 5)
	{
		printf("Error usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Argument %d (%s) is not a positive int number.\n", i, argv[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg			arguments;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;

	if (check(argc, argv))
		return (1);
	arguments.number_of_philosophers = ft_atoi(argv[1]);
	arguments.time_to_die = ft_atoi(argv[2]);
	arguments.time_to_eat = ft_atoi(argv[3]);
	arguments.time_to_sleep = ft_atoi(argv[4]);
	arguments.number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		arguments.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (init_philosophers(&arguments, &philosophers, &forks))
		return (free_all(philosophers, forks, arguments.number_of_philosophers), 1);
	init_threads(&arguments, philosophers);
	free_all(philosophers, forks, arguments.number_of_philosophers);
	return (0);
}
