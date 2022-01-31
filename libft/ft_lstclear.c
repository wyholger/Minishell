/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:33 by wyholger          #+#    #+#             */
/*   Updated: 2021/10/18 17:36:47 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return (1);
	temp = *lst;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp->word);
		free(temp);
	}
	return (0);
}
