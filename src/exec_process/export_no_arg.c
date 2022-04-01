/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:13:17 by wyholger          #+#    #+#             */
/*   Updated: 2022/04/01 18:50:07 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	swap_token(t_list	*sw_tn)
{
	if (sw_tn->prev != 0 && sw_tn->next != 0 && sw_tn->next->next != 0)
	{
		sw_tn->next->prev = sw_tn->prev;
		sw_tn->prev->next = sw_tn->next;
		sw_tn->next->next->prev = sw_tn;
		sw_tn->prev = sw_tn->next;
		sw_tn->next = sw_tn->next->next;
		sw_tn->prev->next = sw_tn;
	}
	else if (sw_tn->prev == 0 && sw_tn->next != 0 && sw_tn->next->next != 0)
	{
		sw_tn->next->prev = sw_tn->prev;
		sw_tn->next->next->prev = sw_tn;
		sw_tn->prev = sw_tn->next;
		sw_tn->next = sw_tn->next->next;
		sw_tn->prev->next = sw_tn;
	}
	else if (sw_tn->prev != 0 && sw_tn->next != 0 && sw_tn->next->next == 0)
	{
		sw_tn->next->prev = sw_tn->prev;
		sw_tn->prev->next = sw_tn->next;
		sw_tn->prev = sw_tn->next;
		sw_tn->next = sw_tn->next->next;
		sw_tn->prev->next = sw_tn;
	}
}

void	print_env_for_export(t_list *lst)
{
	char	**split;

	while (lst != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		split = ft_split(lst->word, '=');
		ft_putstr_fd(split[0], 1);
		if (split[1] != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(split[1], 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		split_free(split);
		lst = lst->next;
	}
}

void	sort_print_env(int size, t_list	*new)
{
	t_list	*tmp;

	while (size >= 0)
	{
		while (new->prev != NULL)
			new = new->prev;
		tmp = new;
		while (tmp != NULL && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->word, tmp->next->word) > 0)
			{
				swap_token(tmp);
				tmp = tmp->prev;
			}
			tmp = tmp->next;
		}
		size--;
	}
	while (new->prev != NULL)
		new = new->prev;
	print_env_for_export(new);
	ft_lstclear(&new);
}

void	export_if_no_arg(t_data *data)
{
	t_list	*tmp_env;
	t_list	*new;
	int		size;

	new = NULL;
	size = ft_lstsize(data->env);
	tmp_env = data->env;
	while (tmp_env != NULL)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp_env->word)));
		tmp_env = tmp_env->next;
	}
	sort_print_env(size, new);
}
