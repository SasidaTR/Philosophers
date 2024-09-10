#include "../include/include.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		printf("Error initializing data\n");
		return (1);
	}
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
