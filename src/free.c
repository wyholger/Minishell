#include "../include/minishell.h"

void	split_free(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
//
// Created by wyholger on 24.12.2021.
//
