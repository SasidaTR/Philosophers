#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						times_must_eat;
	pthread_mutex_t			*forks;
	struct s_philosopher	*philosophers;
}	t_data;

typedef struct s_philosopher
{
	int						id;
	long					last_meal;
	int						meals_eaten;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_t				thread;
	t_data					*data;
}	t_philosopher;

long	current_timestamp(void);
int		init_data(t_data *data, int argc, char **argv);
void	cleanup(t_data *data);
void	*philosopher_routine(void *arg);
void	start_simulation(t_data *data);

int		ft_atoi(const char *str);

#endif
