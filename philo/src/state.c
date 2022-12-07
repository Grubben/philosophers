/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/07 18:47:41 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	takefork(t_philo *philo)
// {
// 	philo_forks_lock(philo);
// 	philo->fleft->setb
// }


void	philo_eat(t_philo *philo)
{
	print_state(philo, EAT);
	philo->lastmeal = get_timestamp(philo->wdata->startstamp);
	
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	philo_forks_unlock(philo);
	philo->forkstaken = 2;
	
	usleep(philo->wdata->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_state(philo, SLEEP);
	philo_forks_lock(philo);
	philo->fleft->setb = 1;
	philo->fright->setb = 1;
	philo_forks_unlock(philo);

	usleep(philo->wdata->time_to_sleep);
	print_state(philo, THINK);
}

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->wdata->allmutex);

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
			pthread_mutex_unlock(&philo->wdata->allmutex);
			philo_die(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->wdata->allmutex);

		// printf("%ld\n", get_timestamp(philo->wdata->startstamp));
		// printf("%ld\n", philo->lastmeal);
		philo_forks_lock(philo);
		if (philo->fleft->setb && philo->fright->setb)
		{
			philo_eat(philo);
			philo_sleep(philo);
		}
		else
			philo_forks_unlock(philo);
	}
}