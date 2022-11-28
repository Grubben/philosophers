/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/28 15:00:01 by amaria-d         ###   ########.fr       */
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
	if (philo->state == THINK)
	{
		printf("%ld %ld is thinking\n", get_time(&philo->wdata->startime), philo->id);
		//TODO: Here is where we'll do the mutex for grabbing
		// tableforks. So protecting the call to statechange(philo, TAKEFORK)
		return (statechange(philo, TAKEFORK));
	}
	if (philo->state == TAKEFORK)
	{
		// pthread_mutex_lock(&philo->wdata->mutex);
		philo->wdata->tableforks -= 1;
		// pthread_mutex_unlock(&philo->wdata->mutex);
		printf("%ld %ld has taken a fork\n", get_time(&philo->wdata->startime), philo->id);
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
		printf("%ld %ld is eating\n", get_time(&philo->wdata->startime), philo->id);
		// usleep(philo->wdata->time_to_eat);
		usleep(2000000);
		//TODO: Must let go of the forks!
		return (statechange(philo, RELEASEFORK));
	}
	if (philo->state == RELEASEFORK)
	{
		printf("%ld %ld is releasing a fork\n", get_time(&philo->wdata->startime), philo->id);
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
		printf("%ld %ld is sleeping\n", get_time(&philo->wdata->startime), philo->id);
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