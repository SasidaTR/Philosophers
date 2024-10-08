/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:21:33 by trischma          #+#    #+#             */
/*   Updated: 2024/10/08 12:23:12 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_params
{
	int				nb_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				mm;
	int				dead;
	struct timeval	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_dead;
}	t_params;

typedef struct s_philo
{
	int				position;
	int				mc;
	long long		time_of_last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	count_mutex;
	t_params		*params;
}	t_philo;

// Actions
void		ft_eat(t_philo *philo);
void		*life(void *arg);
int			is_alive(t_philo *philo, long long current);
int			check_max_meal(t_philo **philos);
void		*death(void *arg);

// Init
int			init_philo(t_philo *philo, t_params *params, int cur);
int			create_table(t_params *params, t_philo **philos);
void		init_params(t_params *params, int argc, char **argv);
void		init_mutex(t_philo *philo, int first_fork, int second_fork);

// Utils
int			ft_atoi(const char *str);
long long	get_timestamp(t_params *params);
int			is_dead(t_philo *philo);
int			check_args(int argc, char **argv);
void		print_action(t_philo *philo, int pos, char *msg);

// Main
void		ft_lock_unlock(t_philo *philo);

#endif