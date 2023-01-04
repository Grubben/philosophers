/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2023/01/04 15:39:45 by amaria-d         ###   ########.fr       */
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
}

// void	changestate(t_philo *philo, int newstate)
// {
// 	if (newstate == philo->state)
// 		return ;
// 	philo->state = newstate;
// 	prot_state(philo, newstate);
// }

void	philo_autodie(t_philo *philo)
{
	pthread_mutex_lock(&philo->wdata->allmutex);
	if (philo->wdata->philo_died == 0)
	{
		// pthread_mutex_lock(&philo->wdata->printlock);
		print_state(philo, DEAD);
		// pthread_mutex_unlock(&philo->wdata->printlock);
		philo->wdata->philo_died = 1;
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
}
