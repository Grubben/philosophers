/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/16 14:32:20 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_anydead(t_philo *philo)
{
	pthread_mutex_lock(&philo->wdata->allmutex);
	if (philo->wdata->philo_died)
	{
		pthread_mutex_unlock(&philo->wdata->allmutex);
		return (1);

	}
	else
		pthread_mutex_unlock(&philo->wdata->allmutex);

	return (0);
}

void	changestate(t_philo *philo, int newstate)
{
	if (newstate == philo->state)
		return ;
	philo->state = newstate;
	print_state(philo, newstate);
}

int	philo_think(t_philo *philo)
{
	philo_forks_lock(philo);
	if (philo->fleft->setb && philo->fright->setb)
	{
		//Alert: Forks left locked
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
			printf("%ld has eaten his last meal\n", philo->id);
			// philo_autodie(philo); We actually don't want to announce he died
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

void	philo_autodie(t_philo *philo)
{
	// Up here I'll undo whatever needs to be done
	//  to kill philo well. eg: unlock stuff
	if (philo->state == EAT)
	{
		//TODO: Do I need to do this?
		philo_forks_lock(philo);
		philo->fleft->setb = 1;
		philo->fright->setb = 1;
		philo_forks_unlock(philo);
	}
	pthread_mutex_lock(&philo->wdata->allmutex);
	if (philo->wdata->philo_died == 0)
	{
		print_state(philo, DEAD);
		philo->wdata->philo_died = 1;
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
	philo->state = DEAD;

}


void	sttchng(t_philo *philo)
{
	suseconds_t	now;

	print_state(philo, THINK);

	now = get_timestamp(philo->wdata->startstamp);
	while (now - philo->lastmeal < philo->wdata->time_to_die)
	{
		if (check_anydead(philo))
		{
			printf("%ld DIED AT CHECK_ANYDEAD\n", philo->id);	
			return ; // Surprisingly this is wrong but has been working
					// should be returning philo_autodie(philo)
		}
		changestate(philo, THINK);
		if (! philo_think(philo))
			continue ;

		if (check_anydead(philo))
		{
			printf("%ld DIED AT CHECK_ANYDEAD\n", philo->id);
			return (philo_autodie(philo));
		}
			
		changestate(philo, TAKEFORK);
		if (! philo_tkforks(philo))
			return ;

		if (check_anydead(philo))
		{
			printf("%ld DIED AT CHECK_ANYDEAD\n", philo->id);			
			return (philo_autodie(philo));
		}
		changestate(philo, EAT);
		if (! philo_eat(philo))
		{
			philo_rlsforks(philo);
			// printf("%ld is disappearing\n_%d__%d\n", philo->id, philo->fleft->setb, philo->fright->setb);
			return ;
		}
		if (check_anydead(philo))
		{
			printf("%ld DIED AT CHECK_ANYDEAD\n", philo->id);
			return (philo_autodie(philo));
		}
		changestate(philo, RELEASEFORK);
		if (! philo_rlsforks(philo))
			return ;
		if (check_anydead(philo))
		{
			printf("%ld DIED AT CHECK_ANYDEAD\n", philo->id);
			return (philo_autodie(philo));
		}
		changestate(philo, RELEASEFORK);
		if (! philo_sleep(philo))
			return ;
		
		now = get_timestamp(philo->wdata->startstamp);
	}
	philo_autodie(philo);
	printf("%ld DIED BY BREAKING\n", philo->id);
}