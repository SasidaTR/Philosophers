#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_args;

int	ft_atoi(const char *str);

#endif