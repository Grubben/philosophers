/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:58 by amaria-d          #+#    #+#             */
/*   Updated: 2023/01/05 16:10:43 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_init(t_fork *fork)
{
	fork->setb = 1;
	pthread_mutex_init(&fork->lock, NULL);
	return (1);
}

int	forks_destroy(t_fork *forks, size_t n_forks)
{
	size_t	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	return (1);
}

int	philo_forks_lock(t_philo *philo)
{
	if ((philo->id & 1) == 1)
	{
		pthread_mutex_lock(&philo->fleft->lock);
		pthread_mutex_lock(&philo->fright->lock);
		return (1);
	}
	pthread_mutex_lock(&philo->fright->lock);
	pthread_mutex_lock(&philo->fleft->lock);
	return (1);
}

int	philo_forks_unlock(t_philo *philo)
{
	if ((philo->id & 1) == 1)
	{
		pthread_mutex_unlock(&philo->fleft->lock);
		pthread_mutex_unlock(&philo->fright->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->fright->lock);
	pthread_mutex_unlock(&philo->fleft->lock);
	return (1);
}

int	philo_forks_set(t_philo *philo)
{
	philo_forks_lock(philo);
	philo->fleft->setb = 1;
	philo->fright->setb = 1;
	philo_forks_unlock(philo);
	return (1);
}

/*
int	philo_forks_tk(t_philo *philo)
{
	philo_forks_lock(philo);
	philo->fleft->setb = 0;
	philo->fright->setb = 0;
	philo_forks_unlock(philo);
	return (1);
}
*/
