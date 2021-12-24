#include "../include/minishell.h"



//
// Created by wyholger on 24.12.2021.
//



char *search_in_envp(t_data *data, char *str)
{
	char 	**for_split;
	char	*result;
	int		i;
	
	i = 0;
	while (data->envp[i])
	{
		for_split = ft_split(data->envp[i], '=');
		if (ft_strcmp(for_split[0], str) == 0)
		{
			result = ft_strcpy(for_split[1]);
			split_free(for_split);
			return(result);
		}
		split_free(for_split);
		i++;
	}
	return (NULL);
}

//Не забываем освободить память переменной result;