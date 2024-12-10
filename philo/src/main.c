/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/10 14:43:39 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_args	args;
	t_sim	*sim;

	memset(&args, 0, sizeof(t_args));
	if (!parsing_process(argc, argv, &args))
		return (1);
	sim = init_sim(&args);
	if (!sim)
		return (1);
	if (!init_philos(sim))
	{
		cleanup_sim(sim);
		return (1);
	}
	cleanup_sim(sim);
	return (0);
}
