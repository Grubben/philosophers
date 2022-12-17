/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/17 20:18:10 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;
	struct timeval	startime;

	gettimeofday(&startime, NULL);
	wdata->startstamp = startime.tv_sec * 1000 + startime.tv_usec / 1000;
	
	// Create philo-threads
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		// 5 micro-seconds
		usleep(1);
		if (i == wdata->n_philos - 1)
			pthread_join(tmphilo->thread, NULL);
	
		i++;
	}
	return (1);
}

void	*philo_go(void *arg)
{
	t_philo	*philo;

	// Init of philo
	philo = (t_philo *)arg;

	// printf("Philosopher %ld Active\n", philo->id);
	
	philo->lastmeal = philo->wdata->startstamp;

	threadmain(philo);
	
	return (NULL);
}

void	threadmain(t_philo *philo)
{
	suseconds_t	now;

	prot_state(philo, THINK);
	now = get_timestamp(philo->wdata->startstamp);
	while (now - philo->lastmeal < philo->wdata->time_to_die)
	{
		if (check_anydead(philo))
			break ;
		changestate(philo, THINK);
		if (! philo_think(philo))
			continue ;
		changestate(philo, TAKEFORK);
		if (! philo_tkforks(philo))
			break ;
		if (check_anydead(philo))
			break ;
		changestate(philo, EAT);
		if (! philo_eat(philo))
			return ((void)philo_rlsforks(philo));
		changestate(philo, RELEASEFORK);
		if (! philo_rlsforks(philo))
			break ;
		if (check_anydead(philo))
			break ;
		changestate(philo, SLEEP);
		if (! philo_sleep(philo))
			break ;		
		now = get_timestamp(philo->wdata->startstamp);
	}
	philo_autodie(philo);
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