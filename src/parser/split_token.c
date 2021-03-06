/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:37:04 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 15:54:12 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_token_space(t_data *data, int *i)
{
	int		k;
	int		j;
	char	*new_token;
	t_list	*new;

	j = 0;
	k = data->breakpoint;
	new_token = malloc(sizeof(char) * (*i - k) + 1);
	if (!new_token)
		return (NULL);
	while (k != (*i))
	{
		new_token[j] = data->str[k];
		k++;
		j++;
	}
	new_token[j] = '\0';
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	new = ft_lstnew(new_token);
	free(new_token);
	return (new);
}

int	ft_chek_around_pipe(t_data *data, int i)
{
	if (data->str[i - 1] == ' ' && data->str[i + 1] == ' ' )
		return (1);
	if (data->str[i - 1] != ' ' && data->str[i + 1] == ' ' )
		return (0);
	if (data->str[i - 1] == ' ' && data->str[i + 1] != ' ' )
		return (1);
	return (0);
}

t_list	*ft_token_pipe(t_data *data, int *i)
{
	int		k;
	int		j;
	char	*new_token;
	t_list	*new;

	j = 0;
	k = data->breakpoint;
	new_token = malloc(sizeof(char) * (*i - k) + 1);
	if (!new_token)
		return (NULL);
	while (k != (*i))
	{
		new_token[j] = data->str[k];
		k++;
		j++;
	}
	new_token[j] = '\0';
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	new = ft_lstnew(new_token);
	free(new_token);
	return (new);
}

t_list	*ft_token_spec(t_data *data, int *i)
{
	int		k;
	char	*new_token;
	t_list	*new;

	k = data->breakpoint;
	new_token = malloc(sizeof(char) * 2);
	if (!new_token)
		return (NULL);
	new_token[0] = data->str[k];
	new_token[1] = '\0';
	(*i)++;
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	new = ft_lstnew(new_token);
	free(new_token);
	return (new);
}

void	ft_pars_token(t_data *data, int i)
{
	data->breakpoint = i;
	while (data->str[i] != '\0')
	{
		if (data->str[i] == '\'' || data->str[i] == '\"')
			ft_help_quo(data, &i);
		if (data->str[i] == ' ')
		{
			ft_lstadd_back(&data->token, ft_token_space(data, &i));
			continue ;
		}
		if (data->str[i] == '|')
		{
			if (ft_chek_around_pipe(data, i) == 0)
			{
				ft_lstadd_back(&data->token, ft_token_pipe(data, &i));
				ft_lstadd_back(&data->token, ft_token_spec(data, &i));
			}
			else
				ft_lstadd_back(&data->token, ft_token_spec(data, &i));
		}
		i++;
	}
	if (data->str[data->breakpoint] != '\0')
		ft_lstadd_back(&data->token, ft_token_space(data, &i));
}
