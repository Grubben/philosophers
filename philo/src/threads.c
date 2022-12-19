/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/19 12:20:32 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Create philo-threads
*/
int	threads_create(t_geninfo *wdata)
{
	size_t			i;
	t_philo			*tmphilo;
	struct timeval	startime;

	gettimeofday(&startime, NULL);
	wdata->startstamp = startime.tv_sec * 1000 + startime.tv_usec / 1000;
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		usleep(1);
		if (i == wdata->n_philos - 1)
			pthread_join(tmphilo->thread, NULL);
		i++;
	}
	return (1);
}

/* Init of philo
*/
void	*philo_go(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// philo->lastmeal = philo->wdata->startstamp;
	philo->lastmeal = 0;

	prot_state(philo, THINK);
	threadmain(philo);
	return (NULL);
}

/* More than 1 philosopher*/
void	threadmain(t_philo *philo)
{
	while (tmsnclstml(philo) < philo->wdata->time_to_die)
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
	while (i < wdata->n_philos - 1)
	{
		tmphilo = &wdata->philarr[i];
		pthread_join(tmphilo->thread, NULL);
		i++;
	}
	return (1);
}
