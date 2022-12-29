/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/29 17:27:46 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_anydead(t_philo *philo)
{
	int	has_died;

	pthread_mutex_lock(&philo->wdata->allmutex);
	has_died = philo->wdata->philo_died;
	pthread_mutex_unlock(&philo->wdata->allmutex);
	return (has_died);
	// if (philo->wdata->philo_died)
	// {
	// 	pthread_mutex_unlock(&philo->wdata->allmutex);
	// 	return (1);
	// }
	// else
	// 	pthread_mutex_unlock(&philo->wdata->allmutex);
	// return (0);
}

void	changestate(t_philo *philo, int newstate)
{
	if (newstate == philo->state)
		return ;
	philo->state = newstate;
	prot_state(philo, newstate);
	// print_state(philo, newstate);
}

void	philo_autodie(t_philo *philo)
{
	//TODO: Check if I need this. I don't think I do
	if (philo->state == EAT)
	{
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
		printf("DEATH_STATE: %d\n", philo->state);
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
	philo->state = DEAD;
}
