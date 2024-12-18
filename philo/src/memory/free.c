/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:34:17 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/18 16:23:43 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>
#include <pthread.h>

void	cleanup_sim(t_sim *sim)
{
    int	i;

    if (!sim)
        return;
    if (sim->philos)
        free(sim->philos);
    if (sim->forks)
    {
        i = 0;
        while (i < sim->args->philo_count)
        {
            pthread_mutex_destroy(&sim->forks[i]);
            i++;
        }
        free(sim->forks);
    }
    pthread_mutex_destroy(&sim->write_lock);
    pthread_mutex_destroy(&sim->death_mutex);
    free(sim);
}
