/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:31 by wyholger          #+#    #+#             */
/*   Updated: 2021/09/27 17:59:32 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = *lst;
		(*lst)->prev = *lst;
	}
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->next == *lst)
			{
				tmp->next = new;
				new->prev = tmp;
				new->next = *lst;
				(*lst)->prev = new;
				*lst = (*lst)->prev;
				break ;
			}
			tmp = tmp->next;
		}
	}
}
