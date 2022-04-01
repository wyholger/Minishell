/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:16:42 by wpitts            #+#    #+#             */
/*   Updated: 2022/04/01 16:22:54 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_redmal(t_list *token, int i)
{
	int	k;

	k = 0;
	while (token != NULL && i != 0)
	{
		if (token->value == 'P')
			i--;
		token = token->next;
	}
	if (token != NULL && token->value == 'P')
		token = token->next;
	while (token != NULL && token->value != 'P')
	{
		if (token->value == 'R')
			return (1);
		token = token->next;
	}
	return (0);
}

int	ft_fill_comm(t_info *des, int p, t_data *data)
{
	t_list	*tmp;

	tmp = data->token;
	while (p != 0)
	{
		while (tmp && tmp->value != 'P')
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		p--;
	}
	if (tmp->value == 'R')
	{
		ft_red_com(tmp, des, p);
		return (1);
	}
	else
	{
		des->command = ft_strdup(tmp->word);
		des->arg[0] = ft_strdup(tmp->word);
		des->arg[1] = NULL;
	}
	return (0);
}

void	ft_des_mal(t_info *des, int p, t_data *data)
{
	des->arg = malloc(sizeof(char **) * ft_len_for_pipe(data->token, p) + 1);
	if (ft_check_redmal(data->token, p) == 1)
	des->red = malloc(sizeof(char **)
				* ft_len_for_pipe2(data->token, p) * 2 + 1);
}

int	ft_fil_fl(t_info *des, t_data *data, int p, int k)
{
	t_list	*tmp;

	tmp = data->token;
	while (p != 0)
	{
		while (tmp && tmp->value != 'P')
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		p--;
	}
	if (tmp->next && ft_strcmp(tmp->next->word, "-n") == 0)
		des->flag = 1;
	if (tmp->next)
	{
		while (tmp->next && ft_strcmp(tmp->next->word, "-n") == 0)
		{
			tmp = tmp->next;
			k++;
		}
	}
	if (des->flag == 1 && k == 0)
		return (1);
	return (k);
}

void	ft_red_fil(t_list *tmp, t_list *tmp1, t_info *des, int *k)
{
	if (ft_strcmp(tmp->word, "4") == 0)
	{
		ft_filling_red(des, tmp1->word);
		des->red[*(k)] = ft_strdup("2");
		des->red[*(k) + 1] = ft_strdup(des->name_her);
	}
	else
	{
		des->red[*(k)] = ft_strdup(tmp->word);
		des->red[*(k) + 1] = ft_strdup(tmp1->word);
	}
	*(k) = *(k) + 2;
}
