/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:17:36 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/23 22:35:06 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hello(void *arg1)
{
	printf("I'm a created thread!\n");
	return (arg1);
}

int	main(void)
{
	pthread_t		th;
	// pthread_attr_t	thattr;

	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	printf("%d\n", pthread_create(&th, NULL, hello, NULL));
	usleep(1000000);

	return (0);
}