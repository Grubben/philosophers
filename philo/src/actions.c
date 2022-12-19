/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:44:38 by endarc            #+#    #+#             */
/*   Updated: 2022/12/19 12:31:18 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Alert: Forks left locked*/
int	philo_think(t_philo *philo)
{
    if (! (philo->fleft && philo->fright))
    {
        if (philo->fleft->setb == 1)
        {
            philo->fleft->setb = 0;
            prot_state(philo, TAKEFORK);
        }
        return (0);
    }
	philo_forks_lock(philo);
	if (philo->fleft->setb && philo->fright->setb)
	{
		return (1);
	}
	else
	{
		philo_forks_unlock(philo);
		return (0);
	}
}

int	philo_tkforks(t_philo *philo)
{
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	philo_forks_unlock(philo);
	return (1);
}

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

int	philo_rlsforks(t_philo *philo)
{
	philo_forks_lock(philo);
	philo->fleft->setb = 1;
	philo->fright->setb = 1;
	philo_forks_unlock(philo);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (! protectedsleep(philo, philo->wdata->time_to_sleep))
		return (0);
	return (1);
}
