/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:21:25 by trischma          #+#    #+#             */
/*   Updated: 2024/10/08 12:21:26 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	init_mutex(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&(philo->params->forks[first_fork]));
	print_action(philo, philo->position, "has taken a fork");
	pthread_mutex_lock(&(philo->params->forks[second_fork]));
	print_action(philo, philo->position, "has taken a fork");
	print_action(philo, philo->position, "is eating");
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->time_of_last_meal = get_timestamp(philo->params);
	pthread_mutex_unlock(&(philo->meal_mutex));
	usleep(1000 * philo->params->time_to_eat);
	pthread_mutex_unlock(&(philo->params->forks[second_fork]));
	pthread_mutex_unlock(&(philo->params->forks[first_fork]));
	pthread_mutex_lock(&(philo->count_mutex));
	philo->mc++;
	pthread_mutex_unlock(&(philo->count_mutex));
}

int	init_philo(t_philo *philo, t_params *params, int cur)
{
	philo->position = cur;
	philo->mc = 0;
	philo->time_of_last_meal = 0;
	philo->right_fork = cur;
	philo->left_fork = (cur + 1) % params->nb_of_philo;
	philo->params = params;
	pthread_mutex_init(&(philo->meal_mutex), NULL);
	pthread_mutex_init(&(philo->count_mutex), NULL);
	if (pthread_create(&(philo->thread), NULL, &life, philo))
		return (0);
	return (1);
}

int	create_table(t_params *params, t_philo **philos)
{
	int	i;

	*philos = malloc(params->nb_of_philo * sizeof (t_philo));
	if (!(*philos))
		return (0);
	params->forks = malloc(params->nb_of_philo * sizeof (pthread_mutex_t));
	if (!params->forks)
	{
		free(*philos);
		return (0);
	}
	i = -1;
	pthread_mutex_lock(&(params->print_mutex));
	while (++i < params->nb_of_philo)
	{
		if (!init_philo(&(*philos)[i], params, i))
		{
			free(*philos);
			free(params->forks);
			return (0);
		}
		pthread_mutex_init(&(params->forks[i]), NULL);
	}
	pthread_mutex_unlock(&(params->print_mutex));
	return (1);
}

void	init_params(t_params *params, int argc, char **argv)
{
	params->nb_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->dead = 0;
	params->mm = -1;
	if (argc > 5)
		params->mm = ft_atoi(argv[5]);
	gettimeofday(&(params->start_time), NULL);
	pthread_mutex_init(&(params->print_mutex), NULL);
	pthread_mutex_init(&(params->check_dead), NULL);
}
