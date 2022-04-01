/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:13:58 by wpitts            #+#    #+#             */
/*   Updated: 2022/04/01 18:02:02 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd_com(t_info *des)
{
	free(des->arg);
	des->arg = malloc(sizeof(char **) * 3);
	des->command = ft_strdup("cd");
	des->arg[0] = ft_strdup("cd");
	des->arg[1] = ft_strdup(".");
	des->arg[2] = NULL;
}

void	ft_just_red(t_list *tmp, t_info *des, int p)
{
	int		k;
	t_list	*tmp1;

	k = 0;
	tmp1 = tmp;
	ft_cd_com(des);
	while (tmp1 && tmp1->value != 'P')
	{
		if (tmp1->value == 'R')
		{
			if (ft_strcmp(tmp1->word, "4") == 0)
				des->name_her = generate_heredoke_name(p);
			ft_red_fil(tmp1, tmp1->next, des, &k);
			tmp1 = tmp1->next;
		}
		tmp1 = tmp1->next;
	}
	des->red[k] = NULL;
}

void	ft_fil_com_arg(t_list *tmp, int i, t_info *des)
{
	if (i == 0)
	{
		des->command = ft_strdup(tmp->word);
		des->arg[0] = ft_strdup(tmp->word);
	}
	else
		des->arg[i] = ft_strdup(tmp->word);
}

void	ft_not_just_red(t_list *tmp, t_info *des, int p)
{
	t_list	*tmp1;
	int		i;
	int		k;

	tmp1 = tmp;
	i = 0;
	k = 0;
	while (tmp1 && tmp1->value != 'P')
	{
		if (tmp1->value == 'W')
		{
			ft_fil_com_arg(tmp1, i, des);
			i++;
		}
		else if (tmp1->value == 'R')
		{
			if (ft_strcmp(tmp1->word, "4") == 0)
				des->name_her = generate_heredoke_name(p);
			ft_red_fil(tmp1, tmp1->next, des, &k);
			tmp1 = tmp1->next;
		}
		tmp1 = tmp1->next;
	}
	des->arg[i] = NULL;
	des->red[k] = NULL;
}

void	ft_red_com(t_list *tmp, t_info *des, int p)
{
	t_list	*tmp1;
	int		k;
	int		i;

	k = 0;
	i = 0;
	tmp1 = tmp;
	while (tmp1 && tmp1->value != 'P')
	{
		if (tmp1->value == 'W')
			i++;
		if (tmp1->value == 'R')
			k++;
		tmp1 = tmp1->next;
	}
	if (tmp1 && tmp1->value == 'P')
	des->pipe = 1;
	if (k / i == 1)
		ft_just_red(tmp, des, p);
	else
		ft_not_just_red(tmp, des, p);
}
