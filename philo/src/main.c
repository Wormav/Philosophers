/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/14 15:49:46 by jlorette         ###   ########.fr       */
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
    usleep(sim->args->time_to_die * 1000);
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
    {
        // Gérer le cas d'un seul philosophe
        return (handle_single_philosopher(sim));
    }

    threads = malloc(sizeof(pthread_t) * args.philo_count);
    if (!threads)
    {
        cleanup_sim(sim);
        return (1);
    }

    i = 0;
    while (i < args.philo_count)
    {
        if (pthread_create(&threads[i], NULL, philosopher_routine, &sim->philos[i]) != 0)
        {
            while (--i >= 0)
                pthread_join(threads[i], NULL);
            free(threads);
            cleanup_sim(sim);
            return (1);
        }
        i++;
    }

    i = 0;
    while (i < args.philo_count)
        pthread_join(threads[i++], NULL);

    free(threads);
    cleanup_sim(sim);
    return (0);
}
