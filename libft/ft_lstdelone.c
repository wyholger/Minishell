/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:37 by wyholger          #+#    #+#             */
/*   Updated: 2022/01/10 10:52:23 by wyholger         ###   ########.fr       */
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
	tmp->next->prev = tmp->prev;
	printf ("WOOOOOOOOOOOOOOOOOOOOOOOORD %s\n", tmp->word);
	free(tmp->word);
	tmp->next = NULL;
	tmp->prev = NULL;
	free(*lst);
	lst = NULL;
}
