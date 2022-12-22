/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 11:56:30 by amaria-d          #+#    #+#             */
/*   Updated: 2022/12/22 15:08:21 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	num;
	signed char		sign;
	size_t			i;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (! (48 <= str[i] && str[i] <= 57))
			return (num * sign);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * sign);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	str_isdigit(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (! is_digit(str[i]))
			return (0);
		i++;
	}
	return (i > 0);
}

/*
int main(void)
{
	printf("%d\n", atoi("    -214748365"));
	printf("%d\n", ft_atoi("    -214748365"));
	return 0;
}
*/
