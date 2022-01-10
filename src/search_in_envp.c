#include "../include/minishell.h"



//
// Created by wyholger on 24.12.2021.
//

t_list	*search_token_in_envp(t_data *data, char *str)
{
	t_list  *tmp;
	char 	**for_split;
	int		i;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		for_split = ft_split(tmp->word, '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			split_free(for_split);
			return(tmp);
		}
		split_free(for_split);
		tmp = tmp->next;
	}
	return (NULL);
}

char *search_in_envp(t_data *data, char *str)
{
	t_list  *tmp;
	char 	**for_split;
	char	*result;
	int		i;
	
	i = 0;
	tmp = data->env;
	while (tmp)
	{
		for_split = ft_split(tmp->word, '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			result = ft_strcpy(for_split[1]);
			split_free(for_split);
			return(result);
		}
		split_free(for_split);
		tmp = tmp->next;
	}
	return (NULL);
}

int search_num_line_in_envp(t_data *data, char *str)
{
	char 	**for_split;
	int		i;
	
	i = 0;
	while (data->envp[i])
	{
		for_split = ft_split(data->envp[i], '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			// result = ft_strcpy(for_split[1]);
			split_free(for_split);
			return(i);
		}
		split_free(for_split);
		i++;
	}
	return (-1);
}

//Не забываем освободить память переменной result;