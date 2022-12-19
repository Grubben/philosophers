/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:58 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/19 12:57:51 by endarc           ###   ########.fr       */
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
