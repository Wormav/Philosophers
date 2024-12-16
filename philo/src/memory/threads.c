/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:54:10 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 09:00:48 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int create_threads(t_sim *sim, t_args *args, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < args->philo_count)
    {
        if (pthread_create(&threads[i], NULL, philosopher_routine, &sim->philos[i]) != 0)
        {
            sim->philos_dead = TRUE;
            while (i >= 0)
			{
                pthread_join(threads[i], NULL);
				i--;
			}
			return (1);
        }
        if (i % 2)
            usleep(1);
        i++;
    }
    return (0);
}

static void monitor_threads(t_args *args, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < args->philo_count)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

int	handle_simulation(t_args *args, t_sim *sim)
{
    pthread_t *threads;

    if (!(threads = malloc(sizeof(pthread_t) * args->philo_count)))
    {
        cleanup_sim(sim);
        return (1);
    }
    if (create_threads(sim, args, threads) != 0)
    {
        free(threads);
        cleanup_sim(sim);
        return (1);
    }
    monitor_threads(args, threads);
    free(threads);
    cleanup_sim(sim);
    return (0);
}
