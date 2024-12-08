/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:50:36 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 15:43:08 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

static char	*trim_leading_zeros(char *str)
{
	char	*trimmed;
	char	*result;
	int		i;
	int		is_negative;

	i = 0;
	is_negative = (str[0] == '-');
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] == '0' && str[i + 1] != '\0')
		i++;
	trimmed = ft_strdup(&str[i]);
	if (is_negative && trimmed[0] != '-')
	{
		result = ft_strjoin("-", trimmed);
		free(trimmed);
		trimmed = result;
	}
	return (trimmed);
}

static void	trim_zero_from_argv(char **argv)
{
	int		i;
	char	*with_sign;

	i = 0;
	while (argv[i])
	{
		with_sign = trim_leading_zeros(argv[i]);
		if (!with_sign)
		{
			argv[i] = NULL;
			return ;
		}
		argv[i] = with_sign;
		i++;
	}
}

static t_bool	is_not_overflow( char *nbr, char *min, char *max)
{
	int	len;
	int	offset;

	offset = 0;
	if (nbr[0] == '+' || nbr[0] == '-')
		offset = 1;
	len = ft_strlen(nbr) - offset;
	if (len > 10)
		return (FALSE);
	if (len < 10)
		return (TRUE);
	if (nbr[0] == '-')
	{
		if (ft_strncmp(nbr, min, ft_strlen(min) + 1) > 0)
			return (FALSE);
	}
	else
	{
		if (ft_strncmp(nbr + offset, max, ft_strlen(max)) > 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	check_args_overflow( char **argv)
{
	int	i;

	i = 0;
	trim_zero_from_argv(argv);
	while (argv[i])
	{
		if (!is_not_overflow(argv[i], "-2147483648", "2147483647"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
