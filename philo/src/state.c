/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/12 15:06:53 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	takefork(t_philo *philo)
// {
// 	philo_forks_lock(philo);
// 	philo->fleft->setb
// }


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

void	sttchng(t_philo *philo)
{
	print_state(philo, THINK);
	while (get_timestamp(philo->wdata->startstamp) - philo->lastmeal < philo->wdata->time_to_die)
	{
		pthread_mutex_lock(&philo->wdata->allmutex);
		if (philo->wdata->philo_died)
		{
			// pthread_mutex_unlock(&philo->wdata->allmutex);
			philo_die(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->wdata->allmutex);

		// printf("%ld\n", get_timestamp(philo->wdata->startstamp));
		// printf("%ld\n", philo->lastmeal);

		if (philo->state == THINK)
		{
			philo_forks_lock(philo);
			if (philo->fleft->setb && philo->fright->setb)
			{
				philo_takeneat(philo);
				// philo_relnsleep(philo);
			}
			else
				philo_forks_unlock(philo);
			continue ;
		}
		if (philo->state == RELEASEFORK)
		{
			philo_relnsleep(philo);
			// usleep(philo->wdata->time_to_eat / 2);
		// 	continue ;
		}
		// if (philo->state == EAT)
		// {
		// 	philo_relnsleep(philo);
		// 	continue ;
		// }
	}
}