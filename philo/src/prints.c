/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:58 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/09 13:38:09 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	print_state(t_philo *philo, int state)
{
	//TODO: use the allmutex for this. might as well
	//TODO: Might have to make this a wdata var because I can't destroy it
	// static pthread_mutex_t printlock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&philo->wdata->printlock);
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
	pthread_mutex_unlock(&philo->wdata->printlock);
}

void   print_autostate(t_philo *philo, int state)
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
