/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:43:03 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 17:56:42 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cansel_quote(t_data *data, int *i)
{
	int	j;

	j = *i + 1;
	while (data->str[j])
	{
		if (data->str[j] == '\'')
		{
			*i = j + 1;
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_cansel_double_quote(t_data *data, int *i)
{
	int	j;

	j = *i + 1;
	while (data->str[j])
	{
		if (data->str[j] == '\"')
		{
			*i = j + 1;
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_check_all_string(t_data *data)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (data->str[0] == ';' || data->str[0] == '|')
		return (1);
	while (data->str[i])
	{
		if (data->str[i] == '\'')
			check = ft_cansel_quote(data, &i);
		if (data->str[i] == '\"')
			check = ft_cansel_double_quote(data, &i);
		if (check == 1)
			return (check);
		i++;
	}
	if (data->str[i - 1] == '|')
		check = 1;
	if (data->str[i - 1] == '<' || data->str[i - 1] == '>')
		check = 1;
	return (check);
}

char	*ft_mal_tmp(t_list *token, char *str)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * ft_strlen(token->word) + ft_strlen(str));
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	ft_help_key(char *tmp, char *str, int *h)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
	{
		tmp[*h] = str[n];
		n++;
		(*h)++;
	}
}
