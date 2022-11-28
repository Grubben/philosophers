/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/28 17:46:53 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	statechange(t_philo *philo, int newstate)
{
	philo->state = newstate;
	if (philo->state == THINK)
	{
		philo->laststatestamp = get_timestamp(philo->wdata->startstamp);
		// printf("%ld %ld is thinking\n", get_time(&philo->wdata->startime), philo->id);
		print_state(philo);
		while (get_timestamp(philo->wdata->startstamp) - philo->laststatestamp < philo->wdata->time_to_die)
		{
			//TODO: Here is where we'll do the mutex for grabbing
			// tableforks. So protecting the call to statechange(philo, TAKEFORK)
			pthread_mutex_lock(&philo->wdata->mutex);
			if (philo->wdata->tableforks > 2)
				return (statechange(philo, TAKEFORK));
			pthread_mutex_unlock(&philo->wdata->mutex);
		}
		// printf("Philosopher has died!\n");
		return (statechange(philo, DEAD)); // Philosopher has died!
	}
	if (philo->state == TAKEFORK)
	{
		//TODO: This shouldn't be necessary since the checking
		// is done in THINK state
		if (philo->wdata->tableforks == 0)
		{
			printf("Error: taking a fork when there is none!\n");
			return ;
		}
		// pthread_mutex_lock(&philo->wdata->mutex);
		philo->wdata->tableforks -= 1;
		//TODO: it's ugly and unclear unlocking in a different state 
		pthread_mutex_unlock(&philo->wdata->mutex);

		print_state(philo);		
		philo->n_forks++;
		
		if (philo->n_forks == 2)
			return (statechange(philo, EAT));
		else // philo->n_forks == 1
			//TODO: Not sure which one I want. Probably THINK
			// return (statechange(philo, TAKEFORK));
			return (statechange(philo, THINK));
	}
	if (philo->state == EAT)
	{
		print_state(philo);
		// usleep(philo->wdata->time_to_eat);
		usleep(2000000);
		//TODO: Must let go of the forks!
		return (statechange(philo, RELEASEFORK));
	}
	if (philo->state == RELEASEFORK)
	{
		print_state(philo);
		// Mutex the releasing of the fork
		pthread_mutex_lock(&philo->wdata->mutex);
		philo->wdata->tableforks++;
		pthread_mutex_unlock(&philo->wdata->mutex);
		
		philo->n_forks -= 1;
		if (philo->n_forks > 0)
			return (statechange(philo, RELEASEFORK));
		else // philo->n_forks == 0
			return (statechange(philo, SLEEP));
	}
	if (philo->state == SLEEP)
	{
		print_state(philo);
		// usleep(philo->wdata->time_to_sleep);
		usleep(2000000);
		return (statechange(philo, THINK));
	}
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(&philo->wdata->mutex);
		print_state(philo);
		philo->wdata->philo_died = 1;
		return ;
	}
}

void	*philo_go(void *arg)
{
	t_philo	*philo;

	// Init of philo
	philo = (t_philo *)arg;

	printf("Philosopher %ld Active\n", philo->id);
	
	philo->laststatestamp = get_time(&philo->wdata->startime);
	statechange(philo, THINK);
	
	return (NULL);
}

int	philostable_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;

	// Needs to be freed!!!
	wdata->philarr = ft_calloc((wdata->n_philos), sizeof(t_philo));
	wdata->forks = malloc((wdata->n_forks) * sizeof(int));
	if (!wdata->philarr && wdata->forks)
		return (0);

	i = 0;
	// Set forks
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		tmphilo->id = i + 1;
		tmphilo->wdata = wdata;

		if (i < wdata->n_forks)
			tmphilo->fleft = &wdata->forks[i];

		i++;
	}
	if ( i < 2)
		return (1); // Not sure if necessary
	i = 0;
	while (i < wdata->n_forks)
	{
		tmphilo = &wdata->philarr[i];
		
		// Right fork of last is left of first
		if (i + 1 == wdata->n_forks)
			tmphilo->fright = wdata->philarr[0].fleft;
		else // right fork of each is left of next
			tmphilo->fright = wdata->philarr[i + 1].fleft;		
	}

	return (1);
}

int	threads_create(t_geninfo *wdata)
{
	size_t	i;
	t_philo	*tmphilo;
	// Create philo-threads
	i = 0;
	while (i < wdata->n_philos)
	{
		tmphilo = &wdata->philarr[i];
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		// 5 micro-seconds
		usleep(5);
		pthread_detach(tmphilo->thread);
		
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
	wattr.time_to_die = 3000;
	// wattr.time_to_eat = ft_atoi(argv[3]);
	// wattr.time_to_sleep = ft_atoi(argv[4]);
	// if (argc == 6)
	// 	wattr.n_must_eat = ft_atoi(argv[5]);
	// else
	// 	wattr.n_must_eat = 0;
	if (argc < 2)
		return (printf("Not enough arguments\n") && 0);

	wattr.n_philos = ft_atoi(argv[1]);

	wattr.tableforks = 1;
	wattr.n_forks = 1;
	
	pthread_mutex_init(&wattr.mutex, NULL);
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

	wattr.philo_died = 0;
	while (wattr.philo_died == 0)
	{
	}
	//TODO: I need to unlock this to destroy it.
	// But do I need to destroy it?
	//ALERT: De-commenting this gives a seg-fault!
	// why??? So it's still locked when program ends
	// pthread_mutex_unlock(&wattr.mutex);

	// This is bad. Just using while learning
	// pthread_join(wattr.philarr[wattr.n_philos - 1].thread, NULL);
	// pthread_join(wattr.philarr[0].thread, NULL);

	// usleep(5000);
	free(wattr.forks);
	free(wattr.philarr);
	return (0);
}