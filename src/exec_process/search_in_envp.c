/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:50:47 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 19:47:48 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*search_token_in_envp(t_data *data, char *str)
{
	t_list	*tmp;
	char	**for_split;

	tmp = data->env;
	while (tmp)
	{
		for_split = ft_split(tmp->word, '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			split_free(for_split);
			return (tmp);
		}
		split_free(for_split);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*search_in_envp(t_data *data, char *str)
{
	t_list	*tmp;
	char	**for_split;
	char	*result;

	tmp = data->env;
	while (tmp)
	{
		for_split = ft_split(tmp->word, '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			result = ft_strcpy(for_split[1]);
			split_free(for_split);
			return (result);
		}
		split_free(for_split);
		tmp = tmp->next;
	}
	return (NULL);
}
