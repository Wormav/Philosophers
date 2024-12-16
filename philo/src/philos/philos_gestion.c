/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:37:25 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 09:30:08 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

t_bool	init_philos(t_sim *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philos) * sim->args->philo_count);
	if (!sim->philos)
	{
		print_error("Error: Failed to initialize philosophers");
		return (FALSE);
	}
	i = 0;
	while (i < sim->args->philo_count)
	{
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].id = i + 1;
		sim->philos[i].last_meal_time = sim->start_time;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1)
			% sim->args->philo_count];
		sim->philos[i].args = sim->args;
		sim->philos[i].sim = sim;
		i++;
	}
	return (TRUE);
}
