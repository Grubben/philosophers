/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/25 23:48:06 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_time(struct timeval *gentime)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	// printf("%ld\n\n", ((now.tv_usec-wdata->startime.tv_usec) / 1000) + ((now.tv_sec - wdata->startime.tv_sec) * 1000));
	return ((now.tv_usec - gentime->tv_usec) / 1000 + ((now.tv_sec - gentime->tv_sec) * 1000));
}

void	statechange(t_philo *philo, int newstate)
{
	philo->state = newstate;
	printf("%ld %ld ", get_time(&philo->wdata->startime), philo->id);
	if (philo->state == TAKEFORK)
	{
		pthread_mutex_lock(&philo->wdata->mutex);
		philo->wdata->tableforks -= 1;
		pthread_mutex_unlock(&philo->wdata->mutex);
		philo->n_forks++;
		
		printf("has taken a fork\n");
		if (philo->n_forks == 2)
			return (statechange(philo, EAT));
	}	
}

void	*philo_go(void *arg)
{
	t_philo	philo;

	// Init of philo
	philo = *(t_philo *)arg;
	philo.state = THINK;
	printf("Philosopher %ld Active\n", philo.id);
	
	while (philo.state != DEAD)
	{
		if (philo.state == THINK)
		{
			statechange(&philo, TAKEFORK);
			// pthread_mutex_lock(philo.mutlock);
		}
	}
	// usleep(6000000);
	return (NULL);
}

int	philos_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;

	// Needs to be freed!!!
	wdata->philarr = ft_calloc((wdata->n_philos), sizeof(t_philo));
	if (!wdata->philarr)
		return (0);
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		tmphilo->id = i + 1;
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		usleep(2000000);
		// pthread_detach(tmphilo->thread);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_geninfo		wattr;

	// if (argc < 5 || argc > 6)
	// 	return (0);
	// wattr.time_to_die = ft_atoi(argv[2]);
	// wattr.time_to_eat = ft_atoi(argv[3]);
	// wattr.time_to_sleep = ft_atoi(argv[4]);
	// if (argc == 6)
	// 	wattr.n_must_eat = ft_atoi(argv[5]);
	// else
	// 	wattr.n_must_eat = 0;
	if (argc < 2)
		return (printf("Not enough arguments\n") && 0);
	wattr.n_philos = ft_atoi(argv[1]);
	wattr.tableforks = wattr.n_philos / 2;
	pthread_mutex_init(&wattr.mutex, NULL);
	gettimeofday(&wattr.startime, NULL);

	if (! philos_create(&wattr))
		return (printf("Philosophers could not be created\n") && 0);

	// This is bad. Just using while learning
	pthread_join(wattr.philarr[wattr.n_philos - 1].thread, NULL);
	// pthread_join(wattr.philarr[0].thread, NULL);

	// usleep(3000000);
	return (0);
}