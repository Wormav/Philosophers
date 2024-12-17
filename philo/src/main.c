/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:16 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

static t_bool	is_case_death_thinking(t_args *args)
{
	return ((args->time_to_eat * 2) > args->time_to_die);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_sim	*sim;

	memset(&args, 0, sizeof(t_args));
	if (!parsing_process(argc, argv, &args))
		return (1);
	if (is_case_death_thinking(&args))
		args.case_death_thinking = TRUE;
	sim = init_sim(&args);
	if (!sim || !init_philos(sim))
	{
		cleanup_sim(sim);
		return (1);
	}
	if (args.philo_count == 1)
		return (handle_single_philosopher(sim));
	return (handle_simulation(&args, sim));
}
