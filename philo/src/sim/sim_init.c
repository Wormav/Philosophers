/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:55:28 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/15 15:21:28 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

static int	init_forks(t_sim *sim, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_write_lock(t_sim *sim)
{
	if (pthread_mutex_init(&sim->write_lock, NULL) != 0)
		return (0);
	return (1);
}

static t_sim	*allocate_sim_and_forks(t_args *args)
{
	t_sim	*sim;

	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (NULL);
	sim->args = args;
	sim->start_time = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!sim->forks)
	{
		free(sim);
		return (NULL);
	}
	sim->start_time = get_time();
	sim->philos_dead = FALSE;
	return (sim);
}

t_sim	*init_sim(t_args *args)
{
	t_sim	*sim;

	sim = allocate_sim_and_forks(args);
	if (!sim)
	{
		print_error("Error: Failed to allocate simulation memory");
		return (NULL);
	}
	if (!init_forks(sim, args->philo_count))
	{
		free(sim->forks);
		free(sim);
		print_error("Error: Failed to initialize forks");
		return (NULL);
	}
	if (!init_write_lock(sim))
	{
		free(sim->forks);
		free(sim);
		print_error("Error: Failed to initialize write lock");
		return (NULL);
	}
	return (sim);
}
