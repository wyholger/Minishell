/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:59:50 by wyholger          #+#    #+#             */
/*   Updated: 2021/10/09 20:09:21 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content_1)
{
	t_list	*begin;

	begin = (t_list *)malloc(sizeof(t_list));
	if (!begin)
		return (NULL);
	begin->next = NULL;
	begin->prev = NULL;
	begin->x = content_1;
	return (begin);
}
