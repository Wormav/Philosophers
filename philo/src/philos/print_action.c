/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:57:34 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/12 15:57:59 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	print_action(t_sim *sim, int philo_id, const char *action)
{
    pthread_mutex_lock(&sim->write_lock);
    printf("%lu Philosopher %d %s\n", get_time() - sim->start_time, philo_id, action);
    pthread_mutex_unlock(&sim->write_lock);
}
