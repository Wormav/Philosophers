/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:00:46 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/12 17:38:20 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>
#include <unistd.h>

void	philosopher_eat(t_philos *philo, t_sim *sim)
{
    pthread_mutex_lock(philo->left_fork);
    print_action(sim, philo->id, PHILO_FORK_MSG);
    pthread_mutex_lock(philo->right_fork);
    print_action(sim, philo->id, PHILO_FORK_MSG);

    pthread_mutex_lock(&sim->write_lock);
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&sim->write_lock);

    print_action(sim, philo->id, PHILO_EAT_MSG);
    usleep(sim->args->time_to_eat * 1000);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void	philosopher_sleep_and_think(t_philos *philo, t_sim *sim)
{
    print_action(sim, philo->id, PHILO_SLEEP_MSG);
    usleep(sim->args->time_to_sleep * 1000);
    print_action(sim, philo->id, PHILO_THINK_MSG);
}

void	*philosopher_routine(void *arg)
{
    t_philo_wrapper *wrapper;
    t_philos *philo;
    t_sim *sim;

	wrapper = (t_philo_wrapper *)arg;
    philo = wrapper->philo;
    sim = wrapper->sim;
    while (!sim->philos_dead)
    {
        philosopher_eat(philo, sim);
        philosopher_sleep_and_think(philo, sim);
	}
    return (NULL);
}
