/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:44:38 by endarc            #+#    #+#             */
/*   Updated: 2022/12/29 17:24:16 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	changestate(philo, THINK);

	if (! (philo->fleft && philo->fright))
	{
		print_state(philo, TAKEFORK);
		myusleep(philo, philo->wdata->time_to_die);
		return (0);
	}

	return (1);
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

int	philo_eat(t_philo *philo)
{
	philo->lastmeal = get_timestamp(philo->wdata->startstamp);
	if (! protectedsleep(philo, philo->wdata->time_to_eat))
		return (0);
	if (philo->wdata->n_must_eat > 0)
	{
		philo->mealseaten++;
		if (philo->mealseaten >= philo->wdata->n_must_eat)
		{
			return (0);
		}
	}
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

int	philo_sleep(t_philo *philo)
{
	if (! protectedsleep(philo, philo->wdata->time_to_sleep))
		return (0);
	return (1);
}
