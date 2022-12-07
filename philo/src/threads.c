/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/07 15:09:26 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;
	// Create philo-threads
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		// 5 micro-seconds
		usleep(50);
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