#include "../include/philo.h"
#include <string.h>

#include <stdio.h>

static void print_philo_forks(t_sim *sim)
{
    int i;
    printf("\n=== Philosophers Forks Configuration ===\n");
    for (i = 0; i < sim->args->philo_count; i++)
    {
        printf("Philosopher %d:\n", sim->philos[i].id);
        printf("  Left fork:  %p (fork %d)\n",
            (void*)sim->philos[i].left_fork,
            (int)(sim->philos[i].left_fork - sim->forks));
        printf("  Right fork: %p (fork %d)\n",
            (void*)sim->philos[i].right_fork,
            (int)(sim->philos[i].right_fork - sim->forks));
        printf("------------------\n");
    }
    printf("\n");
}

// !AJOUTER LA LIGNE DE DESSOUS APRES LA LIGNE 38 DANS routine_utils.c!

// printf("Philo %d took fork at address %p (index: %d)\n",
//         philo->id,
//         (void*)fork,
//         (int)(fork - sim->forks));

static t_bool	is_case_death_thinking(t_args *args)
{
	return ((args->time_to_eat * 2) > args->time_to_die);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_sim	*sim;

	memset(&args, 0, sizeof(t_args));
	if (!parsing_process(argc, argv, &args))
		return (1);
	if (is_case_death_thinking(&args))
		args.case_death_thinking = TRUE;
	sim = init_sim(&args);
	if (!sim || !init_philos(sim))
	{
		cleanup_sim(sim);
		return (1);
	}
	 print_philo_forks(sim);
	if (args.philo_count == 1)
		return (handle_single_philosopher(sim));
	return (handle_simulation(&args, sim));
}
