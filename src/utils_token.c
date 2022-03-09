#include "../include/minishell.h"


int ft_cansel_quote(t_data *data, int *i)
{
	int j;
	
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

int ft_cansel_double_quote(t_data *data, int *i)
{
	int j;
	
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

int ft_check_all_string(t_data *data)
{
	int i;
	int check;
	
	check = 0;
	i = 0;
	if (data->str[0] == ';' || data->str[0] == '|')
		return(1);
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