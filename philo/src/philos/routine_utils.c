/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:05:22 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/15 15:31:20 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>

t_bool	check_death(t_sim *sim, t_philos *philo)
{
	t_bool	is_dead;

	pthread_mutex_lock(&sim->write_lock);
	is_dead = sim->philos_dead;
	if (!is_dead && get_time() - philo->last_meal_time
		> (unsigned long)sim->args->time_to_die)
	{
		printf(PHILO_ID_MSG, get_time() - sim->start_time,
			philo->id, PHILO_DEAD_MSG);
		sim->philos_dead = TRUE;
		is_dead = TRUE;
	}
	pthread_mutex_unlock(&sim->write_lock);
	return (is_dead);
}

static t_bool	take_fork(t_sim *sim, t_philos *philo,
	pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_action(sim, philo, PHILO_FORK_MSG);
	return (TRUE);
}

t_bool	take_forks(t_sim *sim, t_philos *philo,
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (!take_fork(sim, philo, first_fork))
		return (FALSE);
	if (!take_fork(sim, philo, second_fork))
	{
		pthread_mutex_unlock(first_fork);
		return (FALSE);
	}
	return (TRUE);
}

void	select_forks(t_philos *philo,
	pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}
