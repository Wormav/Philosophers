/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:39:08 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 16:13:15 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define ERROR_USAGE_MSG "Error: Invalid numbers arguments for use philo.\n"

# define ARGUMENT_LIMIT_MSG "Error: Arguments INT limits.\n"

# define INVALID_ARG_MSG "Error: Invalid argument format.\n"

# define NEGATIVE_ARG_MSG "Error: Arguments must be non-negative integers.\n"

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_count_required;
}	t_args;

// utils.c
int		ft_atoi( char *str);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
t_bool	is_digit(char c);

// utils_2.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
void	print_error(char *str);

// overflow.c
t_bool	check_args_overflow( char **argv);

// valid_arg.c
t_bool	check_args_format(char **argv);

// parsing.c
t_bool	parsing_process(int argc, char **argv, t_args *args);

#endif
