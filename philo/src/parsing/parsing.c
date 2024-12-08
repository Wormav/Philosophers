/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:21 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 15:42:28 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static t_bool	arg_error_neg(t_args *args)
{
	// ? voir si on peut lancer avec 1 philo
	// if (args->philo_count < 2)
	// {
	// 	printf("Error: philo count must be at least 2\n");
	// 	return (TRUE);
	// }
	if (args->time_to_die < 1 || args->time_to_eat < 1
		|| args->time_to_sleep < 1 || (args->eat_count_required
			&& args->eat_count_required < 1))
		return (TRUE);
	return (FALSE);
}

static void	parse_arg(char	**argv, t_args *args)
{
	args->philo_count = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->eat_count_required = ft_atoi(argv[5]);
}

t_bool	parsing_process(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
	{
		print_error(ERROR_USAGE_MSG);
		return (FALSE);
	}
	if (check_args_overflow(argv))
	{
		print_error(ARGUMENT_LIMIT_MSG);
		return (FALSE);
	}
	if (check_args_format(argv))
	{
		print_error(INVALID_ARG_MSG);
		return (FALSE);
	}
	parse_arg(argv, args);
	if (arg_error_neg(args))
	{
		print_error(NEGATIVE_ARG_MSG);
		return (FALSE);
	}
	return (TRUE);
}