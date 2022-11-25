#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <pthread.h>
# include <sys/time.h>


enum e_PHILOSTATE
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	TAKEFORK
};

typedef struct s_philo t_philo;
typedef struct s_geninfo t_geninfo;

struct s_philo
{
	pthread_t   thread;
	size_t		id;

	int			state; // e_PHILOSTATE
	int			n_forks;

	t_geninfo	*wdata;
};


struct s_geninfo
{
	size_t	n_philos;
	t_philo	*philarr;

	size_t	tableforks;

	size_t  time_to_die;
	size_t  time_to_eat;
	size_t  time_to_sleep;
	size_t  n_must_eat;

	pthread_mutex_t	mutex;

	struct timeval	startime;

};


/*  UTILS   */
int	ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

#endif
