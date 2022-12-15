/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:57 by endarc            #+#    #+#             */
/*   Updated: 2022/12/15 13:40:43 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philostable_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;

	// Both need to be freed!!!
	wdata->philarr = malloc((wdata->n_philos) * sizeof(t_philo));
	// Initializing philarr to 0, so everything is 0
	memset(wdata->philarr, 0, wdata->n_philos * sizeof(t_philo));
	wdata->forks = malloc((wdata->n_forks) * sizeof(t_fork));
	if (! wdata->philarr && wdata->forks)
		return (0);

	i = 0;
	// Set forks
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		tmphilo->id = i + 1;
		tmphilo->wdata = wdata;

		tmphilo->mealseaten = 0;

		// Putting a fork there
		// wdata->forks[i] = 1;
		fork_init(&wdata->forks[i]);
		tmphilo->fleft = &wdata->forks[i];

		i++;
	}
	if ( i < 2)
		return (1); // Not sure if necessary
	i = 0;
	while (i < wdata->n_forks)
	{
		tmphilo = &wdata->philarr[i];
		
		// Right fork of last is left of first
		if (i + 1 == wdata->n_forks)
			tmphilo->fright = wdata->philarr[0].fleft;
		else // right fork of each is left of next
			tmphilo->fright = wdata->philarr[i + 1].fleft;
		
		i++;
	}

	return (1);
}
