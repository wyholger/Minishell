/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:26:32 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 17:31:22 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_alpha_help(t_list *token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (token->word[i] != '$')
		i++;
	j = i + 1;
	while (token->word[j] != '\0' && token->word[j] != '\''
		&& token->word[j] != '\"' && token->word[j] != '$')
	j++;
	return (j - i);
}

int	ft_dollar_digit(t_list *token, t_data *data, int i)
{
	char	*tmp;
	int		k;
	int		h;

	k = 0;
	h = 0;
	tmp = malloc(sizeof(char) * strlen(token->word) - 1);
	if (!tmp)
		return (1);
	while (token->word[i] != '$')
		i++;
	data->breakpoint = i;
	while (token->word[k])
	{
		if (k == i)
			k = k + 2;
		tmp[h] = token->word[k];
		k++;
		h++;
	}
	tmp[h] = '\0';
	free(token->word);
	token->word = tmp;
	return (0);
}

void	ft_skip_to_dol(t_list *token, int *i)
{
	while (token->word[*i] != '$')
	(*i)++;
}

char	*ft_fil_dol_ex(t_list *token, char *tmp, char *str, int i)
{
	int	k;
	int	h;

	h = 0;
	k = 0;
	ft_skip_to_dol(token, &i);
	while (token->word[k])
	{
		if (k == i)
		{
			i = 0;
			while (str[i])
			{
				tmp[h] = str[i];
				h++;
				i++;
			}
			k = k + 2;
		}
		tmp[h] = token->word[k];
		k++;
		h++;
	}
	tmp[h] = '\0';
	return (tmp);
}

int	ft_dollar_exit(t_list *token, t_data *data)
{
	char	*tmp;
	char	*str;

	if (g_exit != 0)
	{
		str = ft_itoa(g_exit);
		data->exit_proc_number = 0;
	}
	else
		str = ft_itoa(data->exit_proc_number);
	tmp = malloc(sizeof(char) * strlen(token->word) + ft_strlen(str) - 1);
	if (!tmp)
		return (1);
	ft_fil_dol_ex(token, tmp, str, 0);
	free(token->word);
	free(str);
	token->word = tmp;
	return (0);
}
