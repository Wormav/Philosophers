/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:39:08 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/06 09:48:34 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define TRUE 1
# define FALSE 0

typedef int			t_bool;

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
char *ft_strdup(char *src);
int ft_strlcpy(char *dest, const char *src, unsigned int size);
int ft_strlen(char *str);
char *ft_strjoin(char const *s1, char const *s2);
int ft_strncmp(char *s1, char *s2, unsigned int n);
int ft_strlcat(char *dest, const char *src,  int size);


// check.c
t_bool	check_args_error( char **argv);

# endif
