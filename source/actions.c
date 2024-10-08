/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:21:31 by trischma          #+#    #+#             */
/*   Updated: 2024/10/08 12:21:32 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int	is_alive(t_philo *philo, long long current)
{
	long long	time_since_eat;

	pthread_mutex_lock(&(philo->meal_mutex));
	time_since_eat = current - philo->time_of_last_meal;
	pthread_mutex_unlock(&(philo->meal_mutex));
	if (time_since_eat > philo->params->time_to_die)
	{
		print_action(philo, philo->position, "died");
		pthread_mutex_lock(&(philo->params->check_dead));
		philo->params->dead = 1;
		pthread_mutex_unlock(&(philo->params->check_dead));
		return (1);
	}
	return (0);
}

int	check_max_meal(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < (*philos)[0].params->nb_of_philo)
	{
		pthread_mutex_lock(&(*philos)[i].count_mutex);
		if ((*philos)[i].mc < (*philos)[0].params->mm)
		{
			pthread_mutex_unlock(&(*philos)[i].count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&(*philos)[i].count_mutex);
		i++;
	}
	return (1);
}

void	*death(void *arg)
{
	t_philo		**philos;
	t_params	*params;
	int			cur;
	int			check;

	philos = (t_philo **)arg;
	params = philos[0]->params;
	check = 0;
	while (!check)
	{
		cur = 0;
		while (cur < params->nb_of_philo)
		{
			if (is_alive(&(*philos)[cur], get_timestamp(params)))
			{
				check = 1;
				break ;
			}
			cur++;
		}
		if (params->mm > 0 && check_max_meal(philos))
			break ;
		usleep(50);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->left_fork > philo->right_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (philo->params->nb_of_philo == 1)
	{
		print_action(philo, 0, "has taken a fork");
		usleep(1000 * philo->params->time_to_die);
		return ;
	}
	init_mutex(philo, first_fork, second_fork);
}

void	*life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	ft_lock_unlock(philo);
	while (!is_dead(philo))
	{
		if (philo->position % 2)
			usleep(1000);
		ft_eat(philo);
		pthread_mutex_lock(&(philo->count_mutex));
		if ((philo->mc >= philo->params->mm && philo->params->mm > 0)
			|| philo->params->nb_of_philo == 1)
		{
			pthread_mutex_unlock(&(philo->count_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->count_mutex));
		usleep(100);
		print_action(philo, philo->position, "is sleeping");
		usleep(1000 * philo->params->time_to_sleep);
		print_action(philo, philo->position, "is thinking");
		if (!(philo->position % 2))
			usleep(500);
	}
	return (NULL);
}
