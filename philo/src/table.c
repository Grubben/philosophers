/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:56:57 by endarc            #+#    #+#             */
/*   Updated: 2022/12/19 12:49:38 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;

	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		tmphilo->id = i + 1;
		tmphilo->wdata = wdata;
		tmphilo->mealseaten = 0;
		fork_init(&wdata->forks[i]);
		tmphilo->fleft = &wdata->forks[i];
		i++;
	}
	if (wdata->n_philos > 1)
		i = 0;
	while (i < wdata->n_forks)
	{
		tmphilo = &wdata->philarr[i];
		if (i + 1 == wdata->n_forks)
			tmphilo->fright = wdata->philarr[0].fleft;
		else
			tmphilo->fright = wdata->philarr[i + 1].fleft;
		i++;
	}
}

/* Creates the table
 * Mallocs twice!
 */
int	philostable_create(t_geninfo *wdata)
{
	wdata->philarr = malloc((wdata->n_philos) * sizeof(t_philo));
	if (! wdata->philarr)
		return (0);
	memset(wdata->philarr, 0, wdata->n_philos * sizeof(t_philo));
	wdata->forks = malloc((wdata->n_forks) * sizeof(t_fork));
	if (! wdata->forks)
		return (0);
	set_forks(wdata);
	return (1);
}
