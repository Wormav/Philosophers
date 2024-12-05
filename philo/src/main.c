/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:52 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/05 15:57:52 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

static t_bool	arg_error(t_args *args)
{
	if (args->philo_count < 2)
	{
		printf("Error: philo count must be at least 2\n");
		return (TRUE);
	}
	if (args->time_to_die < 1 || args->time_to_eat < 1 || args->time_to_sleep < 1 || (args->eat_count_required && args->eat_count_required < 1))
	{
		printf("Error: time to die, eat and sleep must be at least 1\n");
		return (TRUE);
	}
	return (FALSE);
}

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

	if (arg_error(&args))
		return (1);
	return (0);
}
