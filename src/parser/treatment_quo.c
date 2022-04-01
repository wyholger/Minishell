/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_quo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:56:03 by wpitts            #+#    #+#             */
/*   Updated: 2022/04/01 14:58:35 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_help_dquo(t_list *token, t_data *data, int i)
{
	int	k;

	k = i + 1;
	while (token->word[k] != '\"')
	{
		if (token->word[k] == '$')
		{
			ft_tok_dollar(token, k, data);
			return (1);
		}
		k++;
	}
	return (0);
}

int	ft_help_dquo2(t_list *token)
{
	if (token->word && token->word[0] == '\"' && token->word[1] == '\"')
	{
		free(token->word);
		token->word = malloc(sizeof(char) * 1);
		token->word[0] = '\0';
		return (1);
	}
	return (0);
}

int	ft_help_quo1(t_list *token)
{
	if (token->word && token->word[0] == '\'' && token->word[1] == '\'')
	{
		free(token->word);
		token->word = malloc(sizeof(char) * 1);
		token->word[0] = '\0';
		return (1);
	}
	return (0);
}
