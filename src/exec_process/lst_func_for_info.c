/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func_for_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:09:15 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/23 18:24:32 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_info	*info_new(void)
{
	t_info	*begin;

	begin = (t_info *)malloc(sizeof(t_info));
	if (!begin)
		return (NULL);
	begin->next = NULL;
	begin->prev = NULL;
	begin->arg = NULL;
	begin->red = NULL;
	begin->command = NULL;
	begin->flag = 0;
	begin->pipe = 0;
	begin->semocolon = 0;
	begin->redir = NULL;
	begin->name_her = NULL;
	return (begin);
}

void	info_add_back(t_info **lst, t_info *new)
{
	t_info	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
	}
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new;
				new->prev = tmp;
				new->next = NULL;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	info_clear(t_info **lst)
{
	t_info	*temp;

	if (!lst)
		return (1);
	temp = *lst;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp)
		{
			free(temp->command);
			split_free(temp->arg);
			split_free(temp->red);
			free(temp);
		}
	}
	return (0);
}

int	info_size(t_info *lst)
{
	int		i;
	t_info	*sizer;

	i = 0;
	sizer = lst;
	while (sizer)
	{
		i++;
		sizer = sizer->next;
	}
	return (i);
}
