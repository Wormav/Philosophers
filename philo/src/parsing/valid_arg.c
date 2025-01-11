/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:45:05 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/20 08:17:51 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static	t_bool	arg_is_zero(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	is_valid_number(char *arg)
{
	int	i;

	if (!arg || *arg == '\0')
		return (FALSE);
	if (arg[0] == '+' || arg[0] == '-')
	{
		if (!arg[1] || !is_digit(arg[1]))
			return (FALSE);
		i = 1;
	}
	else
	{
		if (!is_digit(arg[0]))
			return (FALSE);
		i = 0;
	}
	while (arg[i])
	{
		if (!is_digit(arg[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	check_args_format(char **argv)
{
	int	i;

	if (arg_is_zero(argv[5]))
	{
		print_error(INVALID_LAST_ARG);
		return (FALSE);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
		{
			print_error(INVALID_ARG_MSG);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
