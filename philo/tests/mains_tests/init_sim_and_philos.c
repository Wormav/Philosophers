#include "../include/philo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	print_philos(t_sim *sim)
{
	int i;

	if (!sim || !sim->philos)
	{
		printf("Simulation or philosophers not initialized.\n");
		return;
	}
	printf("=== Philosopher Information ===\n");
	for (i = 0; i < sim->args->philo_count; i++)
	{
		printf("Philosopher ID: %d\n", sim->philos[i].id);
		printf("  Meals Eaten: %d\n", sim->philos[i].meals_eaten);
		printf("  Last Meal Time: %lu\n", sim->philos[i].last_meal_time);
		printf("  Left Fork: %p\n", (void *)sim->philos[i].left_fork);
		printf("  Right Fork: %p\n", (void *)sim->philos[i].right_fork);
		printf("-------------------------------\n");
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_sim	*sim;

	// Initialisation des arguments
	memset(&args, 0, sizeof(t_args));
	if (!parsing_process(argc, argv, &args))
		return (1);

	// Initialisation de la simulation
	sim = init_sim(&args);
	if (!sim)
	{
		fprintf(stderr, "Error: Failed to initialize simulation\n");
		return (1);
	}

	// Initialisation des philosophes
	if (!init_philos(sim))
	{
		fprintf(stderr, "Error: Failed to initialize philosophers\n");
		free(sim->forks);
		free(sim);
		return (1);
	}

	// Affichage des philosophes pour vérification
	print_philos(sim);

	// Libération des ressources
	int i = 0;
	while (i < args.philo_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->write_lock);
	free(sim->forks);
	free(sim->philos);
	free(sim);

	return (0);
}
