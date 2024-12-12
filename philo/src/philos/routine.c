/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:00:46 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/12 16:56:46 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>
#include <unistd.h>

static void	print_action(t_sim *sim, int philo_id, const char *action)
{
    pthread_mutex_lock(&sim->write_lock);
    printf("%lu Philosopher %d %s\n", get_time() - sim->start_time, philo_id, action);
    pthread_mutex_unlock(&sim->write_lock);
}

void	philosopher_eat(t_philos *philo, t_sim *sim)
{
    pthread_mutex_lock(philo->left_fork);
    print_action(sim, philo->id, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_action(sim, philo->id, "has taken a fork");

    pthread_mutex_lock(&sim->write_lock);
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&sim->write_lock);

    print_action(sim, philo->id, "is eating");
    usleep(sim->args->time_to_eat * 1000);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void	philosopher_sleep_and_think(t_philos *philo, t_sim *sim)
{
    print_action(sim, philo->id, "is sleeping");
    usleep(sim->args->time_to_sleep * 1000);

    print_action(sim, philo->id, "is thinking");
}

void	*philosopher_routine(void *arg)
{
    t_philo_wrapper *wrapper;
    t_philos *philo;
    t_sim *sim;

	wrapper = (t_philo_wrapper *)arg;
    philo = wrapper->philo;
    sim = wrapper->sim;

    printf("Philosopher %d started\n", philo->id);

    while (!sim->philos_dead)
    {
        philosopher_eat(philo, sim);
        philosopher_sleep_and_think(philo, sim);
	}

	printf("Philosopher %d finished\n", philo->id);
    return (NULL);
}
