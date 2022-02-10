/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:37 by wyholger          #+#    #+#             */
/*   Updated: 2022/01/11 15:07:57 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstdelone(t_list **lst)
{
	t_list *tmp;
	
	tmp = *lst;
	if (!lst)
		return ;
	tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->word);
	tmp->next = NULL;
	tmp->prev = NULL;
	free(*lst);
	lst = NULL;
}
