/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:13:09 by amaria-d          #+#    #+#             */
/*   Updated: 2022/10/18 15:05:54 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *head)
{	
	if (head)
	{
		ft_printf("| %i | ", *(int *)(head->content));
		while (head->next != NULL)
		{
			head = head->next;
			ft_printf("%i | ", *(int *)(head->content));
		}
	}
}

void	intptr_printer(void *pointer)
{
	ft_printf("%i\n", *((int *)pointer));
}

void	ft_lstprint2(t_list *head)
{
	ft_lstiter(head, intptr_printer);
}
