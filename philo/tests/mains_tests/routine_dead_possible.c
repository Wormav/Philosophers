#include "../include/philo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int	main(int argc, char **argv)
{
    t_args		args;
    t_sim		*sim;
    pthread_t	*threads;
    t_philo_wrapper *wrappers;
    int			i;

    // ? Initialisation des arguments
    memset(&args, 0, sizeof(t_args));
    if (!parsing_process(argc, argv, &args))
    {
        print_error("Error: Parsing arguments failed\n");
        return (1);
    }
    // ? Initialisation de la simulation
    sim = init_sim(&args);
    if (!sim)
    {
        print_error("Error: Simulation initialization failed\n");
        return (1);
    }
    // ? Initialisation des philosophes
    if (!init_philos(sim))
    {
        print_error("Error: Philosophers initialization failed\n");
        cleanup_sim(sim);
        return (1);
    }
    // ? Création des threads pour les philosophes
    threads = malloc(sizeof(pthread_t) * args.philo_count);
    wrappers = malloc(sizeof(t_philo_wrapper) * args.philo_count);
    if (!threads || !wrappers)
    {
        fprintf(stderr, "Error: Memory allocation for threads or wrappers failed\n");
        cleanup_sim(sim);
        return (1);
    }
	// ? Création des threads
i = 0;
while (i < args.philo_count)
{
    wrappers[i].philo = &sim->philos[i];
    wrappers[i].sim = sim;
    if (pthread_create(&threads[i], NULL, philosopher_routine, &wrappers[i]) != 0)
    {
        print_error("Error: Failed to create thread for philosopher\n");
        while (--i >= 0)
            pthread_join(threads[i], NULL);
        free(threads);
        free(wrappers);
        cleanup_sim(sim);
        return (1);
    }
    i++;
}
    // ? Attente de la fin des threads
	i = 0;
	while (i < args.philo_count)
	{
    	pthread_join(threads[i], NULL);
    	i++;
	}
    // ? Nettoyage final
    free(threads);
    free(wrappers);
    cleanup_sim(sim);
    return (0);
}
