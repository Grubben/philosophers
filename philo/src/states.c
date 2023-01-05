/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:25 by amaria-d          #+#    #+#             */
/*   Updated: 2023/01/05 16:11:47 by amaria-d         ###   ########.fr       */
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
		print_state(philo, DEAD);
		philo->wdata->philo_died = 1;
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
}

int	philo_solo(t_philo *philo)
{
	print_state(philo, THINK);
	print_state(philo, TAKEFORK);
	myusleep(philo, philo->wdata->time_to_die);
	philo_autodie(philo);
	return (1);
}
