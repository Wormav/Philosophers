/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:39:08 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 08:56:50 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define ERROR_USAGE_MSG "Error: Invalid numbers arguments for use philo."

# define ARGUMENT_LIMIT_MSG "Error: Arguments INT limits."

# define INVALID_ARG_MSG "Error: Invalid argument format."

# define NEGATIVE_ARG_MSG "Error: Arguments must be non-negative integers."

# define NO_PHILO_MSG "Error: philo count must be at least 1"

# define PHILO_ID_MSG "⌚ %lu Philosopher %d %s\n\n"

# define PHILO_SLEEP_MSG "is sleeping 🛏️"

# define PHILO_EAT_MSG "is eating 🍝"

# define PHILO_THINK_MSG "is thinking 💭"

# define PHILO_DEAD_MSG "died 💀"

# define PHILO_FORK_MSG "has taken a fork 🍴"

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_count_required;
}	t_args;

typedef struct s_philos
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_args	*args;
	struct s_sim	*sim;
}	t_philos;

typedef struct s_sim
{
	t_args			*args;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	unsigned long	start_time;
	pthread_mutex_t	death_mutex;
	t_bool			philos_dead;
}	t_sim;

// utils.c
int				ft_atoi( char *str);
int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
t_bool			is_digit(char c);

// utils_2.c
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *src);
void			print_error(char *str);

// time.c
unsigned long	get_time(void);
void			sleep_time(unsigned long time, t_philos *philo, t_sim *sim);

// overflow.c
t_bool			check_args_overflow( char **argv);

// valid_arg.c
t_bool			check_args_format(char **argv);

// parsing.c
t_bool			parsing_process(int argc, char **argv, t_args *args);

// sim_init.c
t_sim			*init_sim(t_args *args);

// philos_gestions.c
t_bool			init_philos(t_sim *sim);

// print_action.c
void			print_action(t_sim *sim, t_philos *philo, const char *action);

// routine.c
void			*philosopher_routine(void *arg);

// routine_utils.c
t_bool			check_death(t_sim *sim, t_philos *philo);
t_bool			take_forks(t_sim *sim, t_philos *philo,
					pthread_mutex_t *first_fork, pthread_mutex_t *second_fork);
void			select_forks(t_philos *philo, pthread_mutex_t **first_fork,
					pthread_mutex_t **second_fork);

// free.c
void			cleanup_sim(t_sim *sim);

// single_philo.c
t_bool			handle_single_philosopher(t_sim *sim);

// threads.c
int				handle_simulation(t_args *args, t_sim *sim);

#endif
