/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/12 19:00:14 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;
	// Create philo-threads
	gettimeofday(&wdata->startime, NULL);
	wdata->startstamp = wdata->startime.tv_sec * 1000 + wdata->startime.tv_usec / 1000;
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		// 5 micro-seconds
		// usleep(5);
		if (i == wdata->n_philos - 1)
			pthread_join(tmphilo->thread, NULL);
		// else
		// 	pthread_detach(tmphilo->thread);
	
		i++;
	}
	return (1);
}

/* Only the last thread has been joined
 * Have to join all except last
 * All should have died by now
 *  but this verifies that
*/
int	threads_join(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;

	i = 0;
	while (i <wdata->n_philos - 1)
	{
		tmphilo = &wdata->philarr[i];
		pthread_join(tmphilo->thread, NULL);
		i++;
	}
	return (1);
}