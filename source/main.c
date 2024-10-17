/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:21:17 by trischma          #+#    #+#             */
/*   Updated: 2024/10/17 12:00:43 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	free_all(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < params->nb_of_philo)
	{
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < params->nb_of_philo)
	{
		pthread_mutex_destroy(&(params->forks[i]));
		pthread_mutex_destroy(&((*philos)[i].meal_mutex));
		pthread_mutex_destroy(&((*philos)[i].count_mutex));
		i++;
	}
	pthread_mutex_destroy(&(params->print_mutex));
	pthread_mutex_destroy(&(params->check_dead));
	free(*philos);
	free(params->forks);
}

void	ft_lock_unlock(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->print_mutex));
	pthread_mutex_unlock(&(philo->params->print_mutex));
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage : ./philosophers nb_of_philosophers>0 time_to_die "
			"time_to_eat time_to_sleep nb_of_times_each_philosophers_eat \n"
			"(all time in milliseconds)\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0
		|| (argc > 5 && ft_atoi(argv[5]) <= 0))
	{
		printf("Usage : ./philosophers nb_of_philosophers>0 time_to_die "
			"time_to_eat time_to_sleep nb_of_times_each_philosophers_eat \n"
			"(all time in milliseconds)\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	if (!check_args(argc, argv))
	{
		init_params(&params, argc, argv);
		philos = NULL;
		if (!create_table(&params, &philos))
			return (EXIT_FAILURE);
		death(&philos);
		free_all(&params, &philos);
		return (0);
	}
}
