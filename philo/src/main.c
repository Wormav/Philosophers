/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/13 15:47:34 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// ? si un philo == 1
	if (args.philo_count == 1)
{
    pthread_mutex_lock(sim->philos[0].left_fork);
    print_action(sim, &sim->philos[0], PHILO_FORK_MSG);
    usleep(args.time_to_die * 1000);
    pthread_mutex_lock(&sim->write_lock);
    printf(PHILO_ID_MSG, get_time() - sim->start_time,
        sim->philos[0].id, PHILO_DEAD_MSG);
    pthread_mutex_unlock(&sim->write_lock);
    pthread_mutex_unlock(sim->philos[0].left_fork);
    cleanup_sim(sim);
    return (0);
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
