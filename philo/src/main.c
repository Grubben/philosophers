/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/26 13:18:58 by endarc           ###   ########.fr       */
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

void	statechange(t_philo *philo, int newstate)
{
	philo->state = newstate;
	//TODO: Splitting printf is a horrible idea! The best way would be to make a print-mutex
	// If not worth it at least put all on same line
	printf("%ld %ld ", get_time(&philo->wdata->startime), philo->id);
	if (philo->state == THINK)
	{
		printf("is thinking\n");
		//TODO: Here is where we'll do the mutex for grabbing
		// tableforks. So protecting the call to statechange(philo, TAKEFORK)
		return (statechange(philo, TAKEFORK));
	}
	if (philo->state == TAKEFORK)
	{
		// pthread_mutex_lock(&philo->wdata->mutex);
		philo->wdata->tableforks -= 1;
		// pthread_mutex_unlock(&philo->wdata->mutex);
		printf("has taken a fork\n");
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
		printf("is eating\n");
		// usleep(philo->wdata->time_to_eat);
		usleep(2000000);
		//TODO: Must let go of the forks!
		return (statechange(philo, RELEASEFORK));
	}
	if (philo->state == RELEASEFORK)
	{
		printf("is releasing a fork\n");
		//TODO: mutex this!
		philo->wdata->tableforks++;
		
		philo->n_forks -= 1;
		if (philo->n_forks > 0)
			return (statechange(philo, RELEASEFORK));
		else // philo->n_forks == 0
			return (statechange(philo, SLEEP));
	}
	if (philo->state == SLEEP)
	{
		printf("is sleeping\n");
		// usleep(philo->wdata->time_to_sleep);
		usleep(2000000);
		return (statechange(philo, THINK));
	}
}

void	*philo_go(void *arg)
{
	t_philo	*philo;

	// Init of philo
	philo = (t_philo *)arg;

	printf("Philosopher %ld Active\n", philo->id);
	
	// philo->state = THINK;
	statechange(philo, THINK);
	
	
	// while (philo->state != DEAD)
	// {
	// 	if (philo->state == THINK)
	// 	{
	// 		// pthread_mutex_lock(&philo->wdata->mutex);
	// 		if (philo->wdata->tableforks > 0)
				statechange(philo, TAKEFORK);
			// else
			// 	printf("No forks at the table\n");
			// pthread_mutex_unlock(&philo->wdata->mutex);
	// 	}
	// }
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
		tmphilo->wdata = wdata;
		pthread_create(&(tmphilo->thread), NULL, philo_go, tmphilo);
		usleep(4000000);
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
	// wattr.tableforks = wattr.n_philos / 2;
	wattr.tableforks = 2;
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