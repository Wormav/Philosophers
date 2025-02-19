/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:00:46 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/20 08:18:15 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <unistd.h>

static t_bool	check_all_philos_done(t_sim *sim)
{
	int	i;

	if (!sim->args->eat_count_required)
		return (FALSE);
	pthread_mutex_lock(&sim->write_lock);
	i = 0;
	while (i < sim->args->philo_count)
	{
		if (sim->philos[i].meals_eaten < sim->args->eat_count_required)
		{
			pthread_mutex_unlock(&sim->write_lock);
			return (FALSE);
		}
		i++;
	}
	sim->philos_dead = TRUE;
	pthread_mutex_unlock(&sim->write_lock);
	return (TRUE);
}

static void	handle_meal(t_sim *sim, t_philos *philo)
{
	if (check_death(sim, philo))
		return ;
	pthread_mutex_lock(&sim->write_lock);
	if (!sim->philos_dead)
	{
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&sim->write_lock);
	print_action(sim, philo, PHILO_EAT_MSG);
	sleep_time(sim->args->time_to_eat, philo, sim);
}

static void	philosopher_eat(t_philos *philo, t_sim *sim)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	select_forks(philo, &first_fork, &second_fork);
	if (!take_forks(sim, philo, first_fork, second_fork))
		return ;
	handle_meal(sim, philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	philosopher_sleep_and_think(t_philos *philo, t_sim *sim)
{
	print_action(sim, philo, PHILO_SLEEP_MSG);
	sleep_time(sim->args->time_to_sleep, philo, sim);
	if (!check_all_philos_done(sim))
		print_action(sim, philo, PHILO_THINK_MSG);
	if (sim->args->case_death_thinking)
		sleep_time(sim->args->time_to_eat, philo, sim);
}

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;
	t_sim		*sim;

	philo = (t_philos *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(1);
	while (!check_death(sim, philo))
	{
		philosopher_eat(philo, sim);
		if (check_death(sim, philo) || check_all_philos_done(sim))
			break ;
		philosopher_sleep_and_think(philo, sim);
		usleep(1);
	}
	return (NULL);
}
