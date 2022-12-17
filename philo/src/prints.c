/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:58 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/17 20:13:43 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	print_state(t_philo *philo, int state)
{
	//TODO: Choose between printlock and allmutex
	
	// pthread_mutex_lock(&philo->wdata->printlock);
	// pthread_mutex_lock(&philo->wdata->allmutex);
	// if (philo->wdata->philo_died == 1)
	// {
	// 	pthread_mutex_unlock(&philo->wdata->allmutex);
	// 	return ;
	// }

	if (state == THINK)
	{
		printf("%ld %ld is thinking\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (state == TAKEFORK)
	{
		printf("%ld %ld has taken a fork\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (state == EAT)
	{
		printf("%ld %ld is eating\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (state == RELEASEFORK)
	{
		printf("%ld %ld is releasing a fork\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (state == SLEEP)
	{
		printf("%ld %ld is sleeping\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (state == DEAD)
	{
		printf("%ld %ld died\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	// pthread_mutex_unlock(&philo->wdata->printlock);
	// pthread_mutex_unlock(&philo->wdata->allmutex);
}

void	prot_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->wdata->allmutex);
	if (philo->wdata->philo_died == 0)
	{
		print_state(philo, state);
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
}

void   print_autostate(t_philo *philo)
{ 
	pthread_mutex_lock(&philo->wdata->printlock);
	if (philo->state == THINK)
	{
	printf("%ld %ld is thinking\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (philo->state == TAKEFORK)
	{
	printf("%ld %ld has taken a fork\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (philo->state == EAT)
	{
	printf("%ld %ld is eating\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (philo->state == RELEASEFORK)
	{
	printf("%ld %ld is releasing a fork\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (philo->state == SLEEP)
	{
	printf("%ld %ld is sleeping\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	if (philo->state == DEAD)
	{
		printf("%ld %ld died\n", get_timestamp(philo->wdata->startstamp), philo->id);
	}
	pthread_mutex_unlock(&philo->wdata->printlock);
}
