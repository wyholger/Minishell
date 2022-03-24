/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:38:14 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/23 18:41:57 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstprint_content(t_list **lst)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = *lst;
	while (iter)
	{
		ft_putstr_fd(iter->word, 1);
		write (1, &iter->value, 1);
		ft_putchar_fd('\n', 1);
		iter = iter->next;
		i++;
	}
	return (i);
}
