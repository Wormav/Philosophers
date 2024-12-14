/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:00:46 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/14 16:23:42 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>
#include <unistd.h>

static void	handle_meal(t_sim *sim, t_philos *philo)
{
	pthread_mutex_lock(&sim->write_lock);
	if (!sim->philos_dead)
	{
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&sim->write_lock);
	print_action(sim, philo, PHILO_EAT_MSG);
	usleep(sim->args->time_to_eat * 1000);
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
	usleep(sim->args->time_to_sleep * 1000);
		print_action(sim, philo, PHILO_THINK_MSG);
}

void *philosopher_routine(void *arg)
{
    t_philos *philo;

    philo = (t_philos *)arg;
    while (!check_death(philo->sim, philo))
    {
        philosopher_eat(philo, philo->sim);
        philosopher_sleep_and_think(philo, philo->sim);
    }
    return (NULL);
}
