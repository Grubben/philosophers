/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/22 15:27:35 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_parse(int argc, char *argv[], t_geninfo *wdata)
{
	if (! str_isdigit(argv[1]))
		return (printf("Incorrect argument given\n") && 0);
	wdata->n_philos = ft_atoi(argv[1]);
	if (! str_isdigit(argv[2]))
		return (printf("Incorrect argument given\n") && 0);
	wdata->time_to_die = ft_atoi(argv[2]);
	if (! str_isdigit(argv[3]))
		return (printf("Incorrect argument given\n") && 0);
	wdata->time_to_eat = ft_atoi(argv[3]);
	if (! str_isdigit(argv[4]))
		return (printf("Incorrect argument given\n") && 0);
	wdata->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (! str_isdigit(argv[5]))
			return (printf("Incorrect argument given\n") && 0);
		wdata->n_must_eat = ft_atoi(argv[5]);
		if (wdata->n_must_eat == 0)
			return (0);
	}
	else
		wdata->n_must_eat = 0;
	return (wdata->n_philos && wdata->time_to_die
		&& wdata->time_to_eat && wdata->time_to_sleep);
}

int	main(int argc, char *argv[])
{
	t_geninfo		wattr;

	if (argc < 5 || argc > 6)
		return (printf("Not enough arguments\n") && 0);
	memset(&wattr, 0, sizeof(t_geninfo));
	if (! arg_parse(argc, argv, &wattr))
		return (printf("Incorrect argument given\n") && 0);
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
