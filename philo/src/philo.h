#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_geninfo
{
    size_t  n_philos;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    size_t  n_must_eat;

    size_t  n_forks;
}               t_geninfo;

enum e_PHILOSTATE
{
    EAT,
    SLEEP,
    THINK
};

/*  UTILS   */
int	ft_atoi(const char *str);

#endif
