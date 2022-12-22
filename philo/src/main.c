/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/22 14:13:24 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_geninfo		wattr;

	if (argc < 5 || argc > 6)
		return (printf("Not enough arguments\n") && 0);
	memset(&wattr, 0, sizeof(t_geninfo));
	wattr.n_philos = ft_atoi(argv[1]);
	wattr.time_to_die = ft_atoi(argv[2]);
	wattr.time_to_eat = ft_atoi(argv[3]);
	wattr.time_to_sleep = ft_atoi(argv[4]);
	wattr.n_must_eat = 0;
	if (argc == 6)
		wattr.n_must_eat = ft_atoi(argv[5]);
	wattr.philo_died = 0;
	wattr.n_forks = wattr.n_philos;
	pthread_mutex_init(&wattr.allmutex, NULL);
	if (! philostable_create(&wattr))
		return (printf("Could not create philosophers and forks\n") && 0);
	if (! threads_create(&wattr))
		return (printf("Philosophers threads could not be created\n") && 0);
	threads_join(&wattr);
	pthread_mutex_destroy(&wattr.allmutex);
	forks_destroy(wattr.forks, wattr.n_forks);
	free(wattr.forks);
	free(wattr.philarr);
	return (0);
}
