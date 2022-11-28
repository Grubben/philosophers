/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:56 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/28 15:29:57 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(struct timeval *startime)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	// printf("%ld\n", (now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
	return ((now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
}

suseconds_t	get_timestamp(suseconds_t startstamp)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	// printf("%ld\n", (now.tv_usec - startime->tv_usec) / 1000 + ((now.tv_sec - startime->tv_sec) * 1000));
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - startstamp);	
}
