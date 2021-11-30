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
	t_list	*temp2;
	int		i;

	if (!lst)
		return (0);
	temp2 = *lst;
	i = 0;
	while (*lst)
	{
		if (i != 0 && *lst == temp2)
			break ;
		temp = *lst;
		*lst = (*lst)->next;
		if (temp)
			free(temp);
		i++;
	}
	return (0);
}
