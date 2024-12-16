/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:30:50 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 08:32:42 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

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

t_bool handle_single_philosopher(t_sim *sim)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, single_philo_routine, &sim->philos[0]) != 0)
    {
        print_error("Error: Failed to create thread");
        cleanup_sim(sim);
        return (TRUE);
    }

    pthread_join(thread, NULL);
    cleanup_sim(sim);
    return (FALSE);
}
