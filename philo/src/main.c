/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/15 15:11:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *single_philo_routine(void *arg)
{
    t_philos *philo;
    t_sim    *sim;

    philo = (t_philos *)arg;
    sim = philo->sim;
    print_action(sim, philo, PHILO_FORK_MSG);
    sleep_time(sim->args->time_to_die, philo, sim);
    print_action(sim, philo, PHILO_DEAD_MSG);
    pthread_mutex_lock(&sim->death_mutex);
    sim->philos_dead = TRUE;
    pthread_mutex_unlock(&sim->death_mutex);
    return (NULL);
}

static int handle_single_philosopher(t_sim *sim)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, single_philo_routine, &sim->philos[0]) != 0)
    {
        print_error("Error: Failed to create thread");
        cleanup_sim(sim);
        return (1);
    }

    pthread_join(thread, NULL);
    cleanup_sim(sim);
    return (0);
}


int main(int argc, char **argv)
{
    t_args      args;
    t_sim       *sim;
    pthread_t   *threads;
    int         i;

    memset(&args, 0, sizeof(t_args));
    if (!parsing_process(argc, argv, &args))
    {
        print_error("Error: Parsing arguments failed\n");
        return (1);
    }

    sim = init_sim(&args);
    if (!sim || !init_philos(sim))
    {
        cleanup_sim(sim);
        return (1);
    }

    if (args.philo_count == 1)
        return (handle_single_philosopher(sim));

    if (!(threads = malloc(sizeof(pthread_t) * args.philo_count)))
    {
        cleanup_sim(sim);
        return (1);
    }

    // Création des threads avec délai pour éviter les deadlocks
    for (i = 0; i < args.philo_count; i++)
    {
        if (pthread_create(&threads[i], NULL, philosopher_routine, &sim->philos[i]) != 0)
        {
            sim->philos_dead = TRUE;
            while (--i >= 0)
                pthread_join(threads[i], NULL);
            free(threads);
            cleanup_sim(sim);
            return (1);
        }
        if (i % 2)
            usleep(1); // Délai entre les philosophes pairs et impairs
    }

    // Monitoring des threads
    for (i = 0; i < args.philo_count; i++)
        pthread_join(threads[i], NULL);



    free(threads);
    cleanup_sim(sim);
    return (0);
}
