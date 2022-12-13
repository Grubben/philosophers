/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/13 21:26:06 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	takefork(t_philo *philo)
// {
// 	philo_forks_lock(philo);
// 	philo->fleft->setb
// }

/*
void	philo_takeneat(t_philo *philo)
{
	
	//TODO: Careful here when there is only one philosopher
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	philo_forks_unlock(philo);
	
	philo->forkstaken = 2;
	
	philo->lastmeal = get_timestamp(philo->wdata->startstamp);

	philo->state = EAT;
	print_state(philo, EAT);
	// usleep(philo->wdata->time_to_eat);
	myusleep(philo, philo->wdata->time_to_eat);
	philo->state = RELEASEFORK;
}

void	philo_relnsleep(t_philo *philo)
{
	// Realese the forks
	philo_forks_lock(philo);
	philo->fleft->setb = 1;
	philo->fright->setb = 1;
	philo_forks_unlock(philo);

	philo->state = SLEEP;
	print_state(philo, SLEEP);
	usleep(philo->wdata->time_to_sleep);
	philo->state = THINK;
	print_state(philo, THINK);
}
*/

/*
void	philo_die(t_philo *philo)
{
	// pthread_mutex_lock(&philo->wdata->allmutex);

	if (philo->wdata->philo_died == 1)
	{
		pthread_mutex_unlock(&philo->wdata->allmutex);
		return ;
	}
	
	print_state(philo, DEAD);
	philo->wdata->philo_died = 1;
	pthread_mutex_unlock(&philo->wdata->allmutex);
}
*/

int	philo_tkforks(t_philo *philo)
{
	// philo->state = TAKEFORK;
	// philo_forks_lock(philo);
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	philo_forks_unlock(philo);

	return (1);
}

int	philo_eat(t_philo *philo)
{
	philo->lastmeal = get_timestamp(philo->wdata->startstamp);
	myusleep(philo, philo->wdata->time_to_eat);
	
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
	if (! myusleep(philo, philo->wdata->time_to_sleep))
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
		// philo_forks_lock(philo);
		// philo->fleft->setb = 1;
		// philo->fright->setb = 1;
		// philo_forks_unlock(philo);
		
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

// int	philo_think(t_philo *philo)
// {
// 	philo_forks_lock(philo);
// 	if (philo->fleft->setb && philo->fright->setb)
// 	{
// 		philo->state = TAKEFORK;
// 		print_state(philo, TAKEFORK);
// 		if (! philo_tkforks(philo))
// 			return ;
// 	}
// 	else
// 	{
// 		philo_forks_unlock(philo);
// 		continue ;
// 	}

// }

void	sttchng(t_philo *philo)
{
	suseconds_t	now;
	
	print_state(philo, THINK);
	now = get_timestamp(philo->wdata->startstamp);
	while (now - philo->lastmeal < philo->wdata->time_to_die)
	{
		if (philo->state == DEAD)
			break ;

		if (check_anydead(philo))
			return ;

		philo->state = THINK;
		// print_state(philo, THINK);
		philo_forks_lock(philo);
		if (philo->fleft->setb && philo->fright->setb)
		{
			philo->state = TAKEFORK;
			print_state(philo, TAKEFORK);
			if (! philo_tkforks(philo))
				return ;
		}
		else
		{
			philo_forks_unlock(philo);
			continue ;
		}
		philo->state = EAT;
		if (check_anydead(philo))
			return (philo_autodie(philo));
		print_state(philo, EAT);
		if (! philo_eat(philo))
			return ;
		philo->state = RELEASEFORK;
		if (check_anydead(philo))
			return (philo_autodie(philo));
		print_state(philo, RELEASEFORK);
		if (! philo_rlsforks(philo))
			return ;
		philo->state = SLEEP;
		if (check_anydead(philo))
			return (philo_autodie(philo));
		print_state(philo, SLEEP);
		if (! philo_sleep(philo))
			return ;
		
		now = get_timestamp(philo->wdata->startstamp);

		print_state(philo, THINK);
	}
	philo_autodie(philo);
}