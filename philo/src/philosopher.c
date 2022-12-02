/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:35:39 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/02 18:41:59 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_fork_lock(t_philo *philo)
{
	if ((philo->id & 1) == 1) // id is odd
	{
		pthread_mutex_lock(&philo->fleft->lock);
		pthread_mutex_lock(&philo->fright->lock);			
		return (1);
	}
	else // id is even
	pthread_mutex_lock(&philo->fright->lock);
	pthread_mutex_lock(&philo->fleft->lock);
	return (1);
}

int	philo_fork_unlock(t_philo *philo)
{
	if ((philo->id & 1) == 1) // id is odd
	{
		pthread_mutex_unlock(&philo->fleft->lock);
		pthread_mutex_unlock(&philo->fright->lock);			
		return (1);
	}
	else // id is even
	pthread_mutex_unlock(&philo->fright->lock);
	pthread_mutex_unlock(&philo->fleft->lock);
	return (1);
	
}