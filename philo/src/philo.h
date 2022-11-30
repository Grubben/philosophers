/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:56:46 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/30 17:09:25 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <string.h>

# include <pthread.h>
# include <sys/time.h>

enum e_PHILOSTATE
{
	THINK,
	TAKEFORK,
	EAT,
	RELEASEFORK,
	SLEEP,
	DEAD,
};

typedef struct s_philo		t_philo;
typedef struct s_geninfo	t_geninfo;

struct s_philo
{
	pthread_t	thread;
	size_t		id;

	int			state; // e_PHILOSTATE
	
	int			forkstaken;
	int			*fleft;
	int			*fright;

	suseconds_t	laststatestamp;

	t_geninfo	*wdata;
};

struct s_geninfo
{
	size_t			n_philos;
	
	t_philo			*philarr;

	size_t			n_forks;
	int				*forks;

	long			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			n_must_eat;

	pthread_mutex_t	allmutex;

	struct timeval	startime;
	suseconds_t		startstamp;

	int				philo_died;
};

/*	TIME	*/
suseconds_t	get_time(struct timeval *startime);

suseconds_t	get_timestamp(suseconds_t startstamp);

/*	PRINTS	*/
void		print_state(t_philo *philo);

/*  UTILS   */
int			ft_atoi(const char *str);

void		*ft_calloc(size_t count, size_t size);

#endif
