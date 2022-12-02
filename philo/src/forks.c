/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:15:58 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/02 17:16:54 by amaria-d         ###   ########.fr       */
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
	}
	return (1);
}