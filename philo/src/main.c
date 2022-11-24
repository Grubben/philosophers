/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/24 10:15:23 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hello(void *arg1)
{
	printf("I'm a created thread!\n");
	usleep(1000000);
	return (arg1);
}

int	main(int argc, char *argv[])
{
	pthread_t		th;
	// pthread_attr_t	thattr;
	t_geninfo	worldattr;

	if (argc < 5 || argc > 6)
		return (0);
	
	worldattr.n_philos = ft_atoi(argv[1]);
	worldattr.time_to_die = ft_atoi(argv[2]);
	worldattr.time_to_eat = ft_atoi(argv[3]);
	worldattr.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		worldattr.n_must_eat = ft_atoi(argv[5]);
	else
		worldattr.n_must_eat = 0;
	
	worldattr.n_forks = worldattr.n_philos / 2;




	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	// printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	// printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	// printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	usleep(1000000);

	return (0);
}