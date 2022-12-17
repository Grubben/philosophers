/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:56:46 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/17 20:14:04 by endarc           ###   ########.fr       */
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

typedef struct s_fork
{
	int	setb;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_philo		t_philo;
typedef struct s_geninfo	t_geninfo;

struct s_philo
{
	pthread_t	thread;
	size_t		id;

	int			state; // e_PHILOSTATE
	
	int			forkstaken;
	t_fork		*fleft;
	t_fork		*fright;

	suseconds_t lastmeal;
	size_t		mealseaten;

	t_geninfo	*wdata;
};

struct s_geninfo
{
	size_t			n_philos;
	
	t_philo			*philarr;

	size_t			n_forks;
	t_fork			*forks;

	suseconds_t			time_to_die;
	suseconds_t			time_to_eat;
	suseconds_t			time_to_sleep;
	size_t			n_must_eat;

	pthread_mutex_t	allmutex;
	// pthread_mutex_t	printlock;

	suseconds_t		startstamp;

	int				philo_died;
};

/*	MAIN	*/
void	statechange(t_philo *philo, int newstate);

/*	STATES	*/
void	sttchng(t_philo *philo);

void	philo_autodie(t_philo *philo);

void	philo_die(t_philo *philo);

/*	FORKS	*/
int	fork_init(t_fork *fork);

int	forks_destroy(t_fork *forks, size_t n_forks);

int	philo_forks_lock(t_philo *philo);

int	philo_forks_unlock(t_philo *philo);

/*	TABLE	*/
int	philostable_create(t_geninfo *wdata);

/*	THREADS	*/
void	*philo_go(void *arg);

int	threads_create(t_geninfo *wdata);

int	threads_join(t_geninfo *wdata);

/*	TIME	*/
suseconds_t	get_timestamp(suseconds_t startstamp);

// int	myusleep(t_philo *philo, suseconds_t time_to_x);

int	protectedsleep(t_philo *philo, suseconds_t time_to_x);

/*	PRINTS	*/
void		print_state(t_philo *philo, int state);

void	prot_state(t_philo *philo, int state);

/*  UTILS   */
int			ft_atoi(const char *str);

void		*ft_calloc(size_t count, size_t size);

#endif
