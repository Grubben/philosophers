/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/13 21:39:29 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_geninfo		wattr;

	if (argc < 5 || argc > 6)
	// 	return (0);
	// if (argc < 2)
		return (printf("Not enough arguments\n") && 0);
	
	memset(&wattr, 0, sizeof(t_geninfo));
	
	wattr.n_philos = ft_atoi(argv[1]);
	// Multiplying by 1000 since it's given in miliseconds
	wattr.time_to_die = ft_atoi(argv[2]);// * 1000;
	// wattr.time_to_die = 5000;
	wattr.time_to_eat = ft_atoi(argv[3]);// * 1000;
	wattr.time_to_sleep = ft_atoi(argv[4]);// * 1000;
	// if (argc == 6)
	// 	wattr.n_must_eat = ft_atoi(argv[5]);
	// else
	// 	wattr.n_must_eat = 0;

	wattr.philo_died = 0;
	wattr.n_forks = wattr.n_philos;
	
	pthread_mutex_init(&wattr.printlock, NULL);
	pthread_mutex_init(&wattr.allmutex, NULL);
	
	gettimeofday(&wattr.startime, NULL);
	wattr.startstamp = wattr.startime.tv_sec * 1000 + wattr.startime.tv_usec / 1000;

	// while (1)
	// {
	// 	printf("%ld__", get_time(&wattr.startime));
	// 	printf("%ld\n", get_timestamp(wattr.startstamp));
	// 	usleep(2000000);
	// }

	if (! philostable_create(&wattr))
		return (printf("Could not create philosophers and forks\n") && 0);

	if (! threads_create(&wattr))
		return (printf("Philosophers threads could not be created\n") && 0);

	// while (wattr.philo_died == 0)
	// {
	// }
	// if (wattr.n_philos == 1)
		// pthread_mutex_unlock(&wattr.allmutex); // from the lock when he dies
	printf("PhiloDied: %d\n", wattr.philo_died);
	threads_join(&wattr);
	pthread_mutex_destroy(&wattr.allmutex);
	pthread_mutex_destroy(&wattr.printlock);	
	//TODO: I need to unlock this to destroy it.
	// But do I need to destroy it?
	//ALERT: De-commenting this gives a seg-fault!
	// why??? So it's still locked when program ends
	// pthread_mutex_unlock(&wattr.allmutex);

	// This is bad. Just using while learning
	// pthread_join(wattr.philarr[wattr.n_philos - 1].thread, NULL);
	// pthread_join(wattr.philarr[0].thread, NULL);

	//TODO: this gives time for all the threads to return and die
	// most probably there's a better way
	// usleep(5000000);
	
	forks_destroy(wattr.forks, wattr.n_forks);
	free(wattr.forks);

	free(wattr.philarr);
	return (0);
}