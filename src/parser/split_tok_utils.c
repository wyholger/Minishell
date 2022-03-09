#include "../../include/minishell.h"


void ft_quotes(t_data *data, int *i)
{
    (*i)++;
    while (data->str[*i] != '\'')
        (*i)++;
    (*i)++;
}

void ft_double_quotes(t_data *data, int *i)
{
    (*i)++;
    while (data->str[*i] != '\"')
        (*i)++;
    (*i)++;
}

int ft_skip_space(t_data *data)
{
    int i;

    i = 0;
    while (data->str[i] == ' ')
        i++;
    return (i);

}


void ft_help_quo(t_data *data, int *i)
{
    if (data->str[*i] == '\'')
        ft_quotes(data, i);
    if (data->str[*i] == '\"')
        ft_double_quotes(data, i);
}

