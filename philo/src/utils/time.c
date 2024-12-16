/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:54:46 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/16 08:11:19 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <sys/time.h>
#include <unistd.h>

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_time(unsigned long time, t_philos *philo, t_sim *sim)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (check_death(sim, philo))
			return ;
		usleep(time / 10);
	}
}
