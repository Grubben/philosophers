#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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

typedef struct s_philo t_philo;
typedef struct s_geninfo t_geninfo;

struct s_philo
{
	pthread_t   thread;
	size_t		id;

	int			state; // e_PHILOSTATE
	int			n_forks;

	suseconds_t	laststatestamp;

	t_geninfo	*wdata;
};


struct s_geninfo
{
	size_t	n_philos;
	t_philo	*philarr;

	size_t	tableforks;

	long	time_to_die;
	size_t  time_to_eat;
	size_t  time_to_sleep;
	size_t  n_must_eat;

	pthread_mutex_t	mutex;

	struct timeval	startime;
	suseconds_t	startstamp;

	int	PHILO_DIED;
};

/*	TIME	*/
suseconds_t	get_time(struct timeval *startime);

suseconds_t	get_timestamp(suseconds_t startstamp);


/*	PRINTS	*/
void	print_state(t_philo *philo);

/*  UTILS   */
int	ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

#endif
