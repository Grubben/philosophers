/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/24 21:58:52 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_go(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	printf("Philosopher %ld Active\n", philo.id);
	usleep(6000000);
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
		usleep(1000000);
		pthread_detach(tmphilo->thread);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_geninfo		worldattr;
	struct timeval	clock;
	suseconds_t		startime;
	
	// if (argc < 5 || argc > 6)
	// 	return (0);
	if (argc < 2)
		return (printf("Not enough arguments\n") && 0);
	worldattr.n_philos = ft_atoi(argv[1]);
	// worldattr.n_forks = worldattr.n_philos / 2;

	
	gettimeofday(&clock, NULL);
	startime = clock.tv_usec;
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);
	
	gettimeofday(&clock, NULL);
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);
	
	gettimeofday(&clock, NULL);
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);

	gettimeofday(&clock, NULL);
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);

	gettimeofday(&clock, NULL);
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);

	gettimeofday(&clock, NULL);
	printf("%d\n", clock.tv_usec - startime);
	usleep(1000000);

	// worldattr.time_to_die = ft_atoi(argv[2]);
	// worldattr.time_to_eat = ft_atoi(argv[3]);
	// worldattr.time_to_sleep = ft_atoi(argv[4]);
	// if (argc == 6)
	// 	worldattr.n_must_eat = ft_atoi(argv[5]);
	// else
	// 	worldattr.n_must_eat = 0;

	if (! philos_create(&worldattr))
		return (printf("Philosophers could not be created\n") && 0);
	// usleep(3000000);
	// worldattr.philarr = ft_calloc((worldattr.n_philos), sizeof(t_philo));
	// tmphilo = worldattr.philarr[0];
	// tmphilo.id = 0 + 1;
	// pthread_create(&(worldattr.philarr[0].thread), NULL, philo_go, &tmphilo);


	// This is bad. Just using while learning
	// pthread_join(worldattr.philarr[worldattr.n_philos - 1].thread, NULL);
	// pthread_join(worldattr.philarr[0].thread, NULL);

	usleep(3000000);
	return (0);
}