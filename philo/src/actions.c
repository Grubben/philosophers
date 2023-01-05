/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:44:38 by endarc            #+#    #+#             */
/*   Updated: 2023/01/05 16:12:03 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	philo_forks_lock(philo);
	if (philo->fleft->setb && philo->fright->setb)
	{
		philo->fleft->setb = 0;
		philo->fright->setb = 0;
		philo_forks_unlock(philo);
		return (1);
	}
	philo_forks_unlock(philo);
	return (0);
}

/*
int	philo_tkforks(t_philo *philo)
{
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	// philo_forks_unlock(philo);
	return (1);
}
*/

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

int	philo_eat(t_philo *philo)
{
	if (tmsnclstml(philo) > philo->wdata->time_to_die)
		return (0);
	philo->lastmeal = get_timestamp(philo->wdata->startstamp);
	if (philo->wdata->n_must_eat > 0)
	{
		philo->mealseaten++;
		if (philo->mealseaten >= philo->wdata->n_must_eat)
		{
			return (0);
		}
	}
	if (! protectedsleep(philo, philo->wdata->time_to_eat))
		return (0);
	return (1);
}
/*
int	philo_rlsforks(t_philo *philo)
{
	// philo_forks_lock(philo);
	philo->fleft->setb = 1;
	philo->fright->setb = 1;
	philo_forks_unlock(philo);
	return (1);
}
*/

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

int	philo_sleep(t_philo *philo)
{
	if (! protectedsleep(philo, philo->wdata->time_to_sleep))
		return (0);
	return (1);
}
