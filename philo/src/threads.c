/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:54:01 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/29 20:31:43 by amaria-d         ###   ########.fr       */
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
	// prot_state(philo, THINK);
	if (philo->wdata->n_philos == 1)
		philo_solo(philo);
	else
		threadmain(philo);
	return (NULL);
}

int	tkneat(t_philo *philo)
{
	int	has_died;
	
	pthread_mutex_lock(&philo->wdata->allmutex);
	has_died = philo->wdata->philo_died;
	if (has_died == 0)
	{		
		print_state(philo, TAKEFORK);
		print_state(philo, TAKEFORK);
		print_state(philo, EAT);
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
	return (has_died);
}

int	presleep(t_philo *philo)
{
	int	has_died;
	
	pthread_mutex_lock(&philo->wdata->allmutex);
	has_died = philo->wdata->philo_died;
	if (has_died == 0)
	{		
		print_state(philo, SLEEP);
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
	return (has_died);
}

/* Only accessed when there is more than 1 philosopher*/
void	threadmain(t_philo *philo)
{
	while (tmsnclstml(philo) < philo->wdata->time_to_die)
	{
		prot_state(philo, THINK);
		philo_forks_lock(philo);

		if (tkneat(philo))
		{
			philo_forks_unlock(philo);
			break ;
		}
		if (! philo_eat(philo))
		{
			philo_forks_unlock(philo);
			return ;
		}

		philo_forks_unlock(philo);
		if (presleep(philo))
			break ;
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
