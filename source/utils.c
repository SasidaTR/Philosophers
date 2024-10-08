/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:21:28 by trischma          #+#    #+#             */
/*   Updated: 2024/10/08 12:21:29 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	print_action(t_philo *philo, int pos, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&(philo->params->check_dead));
	if (philo->params->dead)
	{
		pthread_mutex_unlock(&(philo->params->check_dead));
		return ;
	}
	pthread_mutex_unlock(&(philo->params->check_dead));
	timestamp = get_timestamp(philo->params);
	pthread_mutex_lock(&(philo->params->print_mutex));
	printf("%08lld %d %s\n", timestamp, pos + 1, msg);
	pthread_mutex_unlock(&(philo->params->print_mutex));
}

int	is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&(philo->params->check_dead));
	is_dead = philo->params->dead;
	pthread_mutex_unlock(&(philo->params->check_dead));
	return (is_dead);
}

long long	get_timestamp(t_params *params)
{
	struct timeval	tv;
	long long		ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec - params->start_time.tv_sec) * 1000
		+ (tv.tv_usec - params->start_time.tv_usec) / 1000;
	return (ts);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
