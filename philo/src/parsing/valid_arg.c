/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:45:05 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 17:13:30 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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

	i = 0;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
