/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 15:38:15 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

int	main(int argc, char	**argv)
{
	t_args	args;

	if (!parsing_process(argc, argv, &args))
		return (1);
	printf("philo count: %d\n", args.philo_count);
	printf("time to die: %d\n", args.time_to_die);
	printf("time to eat: %d\n", args.time_to_eat);
	printf("time to sleep: %d\n", args.time_to_sleep);
	if (argc == 6)
		printf("eat count required: %d\n", args.eat_count_required);
	return (0);
}
