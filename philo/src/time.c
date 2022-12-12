/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:56 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/12 15:31:51 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(struct timeval *startime)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	// printf("%ld\n", (now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
	return ((now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
}

suseconds_t	get_timestamp(suseconds_t startstamp)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	// printf("%ld\n", (now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - startstamp);	
}

/*Implementing my own usleep*/
void	myusleep(t_philo *philo, suseconds_t time_to_x)
{
	suseconds_t	sleepstart;
	suseconds_t	now;

	sleepstart = get_timestamp(philo->wdata->startstamp);
	now = get_timestamp(philo->wdata->startstamp);
	while (now - sleepstart < time_to_x)
	{
		//TODO: Massively rework this section!
		if (now - sleepstart > philo->wdata->time_to_die)
		{
			// Realese the forks
			philo_forks_lock(philo);
			philo->fleft->setb = 1;
			philo->fright->setb = 1;
			philo_forks_unlock(philo);
			philo_die(philo);
		}
		now = get_timestamp(philo->wdata->startstamp);
	}
	printf("Done eating!\n");
}