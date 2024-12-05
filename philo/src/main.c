/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/05 15:25:02 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

static void	parse_arg(char const **argv, t_args *args)
{
	args->philo_count = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->eat_count_required = ft_atoi(argv[5]);
}

int main(int argc, char const **argv)
{
	t_args args;

	if (argc < 5)
		return (1);
	parse_arg(argv, &args);
	printf("philo count: %d\n", args.philo_count);
	printf("time to die: %d\n", args.time_to_die);
	printf("time to eat: %d\n", args.time_to_eat);
	printf("time to sleep: %d\n", args.time_to_sleep);
	if (argc == 6)
		printf("eat count required: %d\n", args.eat_count_required);
	return (0);
}
