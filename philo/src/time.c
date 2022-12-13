/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:56 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/13 21:46:56 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_timestamp(suseconds_t startstamp)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - startstamp);	
}

/*Implementing my own usleep*/
int	myusleep(t_philo *philo, suseconds_t time_to_x)
{
	suseconds_t	sleepstart;
	suseconds_t	now;

	sleepstart = get_timestamp(philo->wdata->startstamp);
	now = get_timestamp(philo->wdata->startstamp);
	while (now - sleepstart < time_to_x)
	{
		//TODO: Massively rework this section!
		if (now - philo->lastmeal > philo->wdata->time_to_die)
		{
			philo_autodie(philo);
			return (0);
		}
		usleep(1); // not sure if this does anything
		now = get_timestamp(philo->wdata->startstamp);
	}
	// printf("Done eating!\n");
	return (1);
}