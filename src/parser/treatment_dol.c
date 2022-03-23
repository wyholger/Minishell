/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_dol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:18:53 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 17:58:56 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_it_is_key(t_list *token, char *str, int i, int k)
{
	char	*tmp;
	int		h;
	int		n;

	n = 0;
	h = 0;
	tmp = ft_mal_tmp(token, str);
	if (!tmp)
		return (1);
	ft_skip_to_dol(token, &i);
	while (token->word[k] != '\0')
	{
		if (k == i)
		{
			ft_help_key(tmp, str, &h);
			k = k + ft_alpha_help(token);
		}
		tmp[h] = token->word[k];
		k++;
		h++;
	}
	free(token->word);
	token->word = tmp;
	return (0);
}

int	ft_dollar_alpha(t_list *token, int j)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	ft_skip_to_dol(token, &i);
	k = i;
	while (token->word[i] != '\0')
		i++;
	tmp = malloc(sizeof(char) * i - ft_alpha_help(token));
	if (!tmp)
		return (1);
	i = 0;
	while (token->word[i] != '\0')
	{
		if (i == k)
			i = i + ft_alpha_help(token);
		tmp[j] = token->word[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(token->word);
	token->word = tmp;
	return (0);
}

int	ft_dollar(t_list *token, char *str, t_data *data)
{
	char	*tmp;

	tmp = search_in_envp(data, str);
	if (tmp != NULL)
	{
		ft_it_is_key(token, tmp, 0, 0);
		free(tmp);
	}
	else
	{
		if (ft_isalpha(str[0]) == 1)
			ft_dollar_alpha(token, 0);
		else if (ft_isdigit(str[0]) == 1)
			ft_dollar_digit(token, data, 0);
		else if (str[0] == '?')
			ft_dollar_exit(token, data);
	}
	return (0);
}

int	ft_tok_dollar(t_list *token, int i, t_data *data)
{
	int		k;
	int		j;
	char	*tmp;

	k = 0;
	j = i + 1;
	while (token->word[j] != '\0' && token->word[j] != '\''
		&& token->word[j] != '\"' && token->word[j] != '$')
		j++;
	tmp = malloc(sizeof(char) * (j - i) + 1);
	if (!tmp)
		return (1);
	i = i + 1;
	while (i != j)
	{
		tmp[k] = token->word[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	ft_dollar(token, tmp, data);
	free(tmp);
	return (0);
}
