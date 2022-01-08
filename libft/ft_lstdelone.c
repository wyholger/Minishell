/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:37 by wyholger          #+#    #+#             */
/*   Updated: 2022/01/08 21:06:51 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst)
{
    t_list *tmp;
    
	tmp = *lst;
    if (!lst)
		return ;
	tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp->word);
    tmp->next = NULL;
    tmp->prev = NULL;
	free(lst);
	lst = NULL;
}
