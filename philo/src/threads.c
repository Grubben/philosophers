/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/29 16:36:00 by amaria-d         ###   ########.fr       */
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
	philo->lastmeal = 0;
	prot_state(philo, THINK);
	threadmain(philo);
	return (NULL);
}

/* Now works with 1 philosopher and more*/
void	threadmain(t_philo *philo)
{
	//TODO: Not stopping when I specify meals to eat
	while (tmsnclstml(philo) < philo->wdata->time_to_die)
	{
		changestate(philo, THINK);
		philo_forks_lock(philo);
		if (check_anydead(philo))
		{
			philo_forks_unlock(philo);
			break ;
		}
		changestate(philo, TAKEFORK);
		changestate(philo, EAT);
		//TODO: Check if protection is needed
		if (! philo_eat(philo))
		{
			philo_forks_unlock(philo);
			return ; //TODO: Do something when amount of meals reached
		}
		if (check_anydead(philo))
		{
			philo_forks_unlock(philo);	
			break ;
		}
		changestate(philo, RELEASEFORK);
		philo_forks_unlock(philo);
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
