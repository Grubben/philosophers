/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2023/01/05 16:09:52 by amaria-d         ###   ########.fr       */
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
	philo->lastmeal = philo->wdata->startstamp;
	if (philo->wdata->n_philos == 1)
		philo_solo(philo);
	else
	{
		prot_state(philo, THINK);
		if (philo->id % 2)
			usleep(1500);
		threadmain(philo);
	}
	return (NULL);
}

/* Only accessed when there is more than 1 philosopher*/
void	threadmain(t_philo *philo)
{
	while (tmsnclstml(philo) < philo->wdata->time_to_die)
	{
		if (! philo_think(philo))
			continue ;
		if (tkneat(philo))
		{
			philo_forks_set(philo);
			break ;
		}
		if (! philo_eat(philo))
		{
			philo_forks_set(philo);
			return ;
		}
		philo_forks_set(philo);
		if (presleep(philo))
			break ;
		if (! philo_sleep(philo))
			break ;
		if (prot_state(philo, THINK))
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
