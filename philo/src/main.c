/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 09:38:11 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

int	main(int argc, char **argv)
{
    t_args      args;
    t_sim       *sim;

    memset(&args, 0, sizeof(t_args));
    if (!parsing_process(argc, argv, &args))
    {
        print_error("Error: Parsing arguments failed\n");
        return (1);
    }
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
