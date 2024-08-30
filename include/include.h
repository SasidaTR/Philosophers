#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				philosophers_done_eating;
	pthread_mutex_t	done_eating_mutex;
	int				simulation_running;
	pthread_mutex_t	simulation_mutex;
}	t_arg;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_arg			*arguments;
}	t_philosopher;

int		ft_atoi(const char *str);
void	free_all(t_philosopher *philosophers, pthread_mutex_t *forks, int number_of_philosophers);
void	print_status(t_philosopher *philo, const char *status);

// actions
void	sleep_and_think(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	put_forks(t_philosopher *philo);
void	take_forks(t_philosopher *philo);
void	check_death(t_philosopher *philo);

#endif