/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:57:34 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/13 12:18:49 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>

void print_action(t_sim *sim, t_philos *philo, const char *action)
{
    pthread_mutex_lock(&sim->write_lock);
    if (!sim->philos_dead)
        printf(PHILO_ID_MSG, get_time() - sim->start_time, philo->id, action);
    pthread_mutex_unlock(&sim->write_lock);
}
