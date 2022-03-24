/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:45:11 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 16:55:38 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_fill_arg3(t_info *des, t_list *tmp, int *i)
{
	des->arg[(*i)] = ft_strdup(tmp->word);
	(*i)++;
}

void	ft_fill_arg1(t_info *des, t_list *tmp, int p, int z)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (tmp && tmp->value != 'P')
	{
		if (tmp->value == 'W' && ft_strcmp(tmp->word, "-n") != 0)
			ft_fill_arg3(des, tmp, &i);
		if (tmp->value == 'R')
		{
			if (ft_strcmp(tmp->word, "4") == 0)
				des->name_her = generate_heredoke_name(p);
			ft_red_fil(tmp, tmp->next, des, &k);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->value == 'P')
		des->pipe = 1;
	des->arg[i] = NULL;
	if (z == 1)
		des->red[k] = NULL;
}

void	ft_fill_arg(t_info *des, t_data *data, int p, int c)
{
	t_list	*tmp;
	int		k;

	tmp = data->token;
	while (c < p)
	{
		while (tmp && tmp->value != 'P')
			tmp = tmp->next;
		if (tmp->next && tmp->value == 'P')
			tmp = tmp->next;
		c++;
	}
	if (tmp->next)
		tmp = tmp->next;
	k = ft_fil_fl(des, data, p, 0);
	while (tmp->next && k != 0)
	{
		tmp = tmp->next;
		k--;
	}
	if (ft_check_redmal(data->token, p) == 1)
		ft_fill_arg1(des, tmp, p, 1);
	else
		ft_fill_arg1(des, tmp, p, 0);
}

void	ft_filling_info(t_data *data, int p)
{
	t_info	*des;
	t_list	*tmp;

	tmp = data->token;
	des = data->info;
	while (tmp != NULL)
	{
		des = info_new();
		ft_des_mal(des, p, data);
		ft_fill_comm(des, p, data);
		if (tmp->next)
		{
			tmp = tmp->next;
			ft_fill_arg(des, data, p, 0);
		}
		while (tmp && tmp->value != 'P')
			tmp = tmp->next;
		info_add_back(&data->info, des);
		if (tmp != NULL)
			tmp = tmp->next;
		init_heredok(des);
		des = des->next;
		p++;
	}
}
