/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:56:40 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 16:18:33 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_red_new(t_list *token, int i)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return ;
	if (i == 1)
		tmp[0] = '1';
	if (i == 2)
		tmp[0] = '2';
	if (i == 3)
		tmp[0] = '3';
	if (i == 4)
		tmp[0] = '4';
	if (i == 5)
		tmp[0] = '5';
	if (i == 6)
		tmp[0] = '6';
	tmp[1] = '\0';
	free(token->word);
	token->word = tmp;
}

void	ft_token_red_treat(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->value == 'R')
		{
			if (tmp->word[0] == '<' && !tmp->word[1])
				ft_red_new(tmp, 2);
			if (tmp->word[0] == '>' && !tmp->word[1])
				ft_red_new(tmp, 1);
			if (tmp->word[0] == '<' && tmp->word[1] && tmp->word[1] == '<')
				ft_red_new(tmp, 4);
			if (tmp->word[0] == '>' && tmp->word[1] && tmp->word[1] == '>')
				ft_red_new(tmp, 3);
			if (tmp->word[0] == '2' && tmp->word[1] && tmp->word[1] == '>'
				&& !tmp->word[2])
				ft_red_new(tmp, 5);
			if (tmp->word[0] == '2' && tmp->word[1] && tmp->word[1] == '>'
				&& tmp->word[2] && tmp->word[2] == '>')
				ft_red_new(tmp, 6);
		}
		tmp = tmp->next;
	}
}

int	ft_tilda(t_list *token, t_data *data, int i, int k)
{
	char	*tmp;

	if (token->word[1] != '\0' && token->word[1] != '/')
		return (1);
	tmp = malloc(sizeof(char) * ft_strlen(token->word)
			+ ft_strlen(data->pwd_home));
	if (!tmp)
		return (1);
	while (data->pwd_home[i++])
	{
		tmp[k] = data->pwd_home[i];
		k++;
	}
	i = 1;
	if (token->word[1] == '/')
		tmp[k - 1] = '/';
	while (token->word[i++])
	{
		tmp[k] = token->word[i];
		k++;
	}
	tmp[k] = '\0';
	free(token->word);
	token->word = tmp;
	return (0);
}
