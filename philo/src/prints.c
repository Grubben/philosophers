/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:58 by amaria-d          #+#    #+#             */
/*   Updated: 2023/01/04 13:48:37 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, int state)
{
	printf("%ld %ld ", get_timestamp(philo->wdata->startstamp), philo->id);
	if (state == THINK)
	{
		printf("is thinking\n");
	}
	else if (state == TAKEFORK)
	{
		printf("has taken a fork\n");
	}
	else if (state == EAT)
	{
		printf("is eating\n");
	}
	else if (state == RELEASEFORK)
	{
		printf("is releasing a fork\n");
	}
	else if (state == SLEEP)
	{
		printf("is sleeping\n");
	}
	else if (state == DEAD)
	{
		printf("died\n");
	}
}

/* Prints philo state if no philosopher has died*/
int	prot_state(t_philo *philo, int state)
{
	int	has_died;
	pthread_mutex_lock(&philo->wdata->allmutex);
	has_died = philo->wdata->philo_died;
	if (has_died == 0)
	{
		print_state(philo, state);
		if (state == TAKEFORK || state == RELEASEFORK)
			print_state(philo, state);
	}
	pthread_mutex_unlock(&philo->wdata->allmutex);
	return (has_died);
}
