#include "../../include/minishell.h"


int ft_help_dquo(t_list *token, t_data *data, int i)
{
    int k;

    k = i + 1;
    while (token->word[k] != '\"')
    {
        if (token->word[k] == '$')
            ft_tok_dollar(token, k, data);
        k++;
    }
    return (0);
}

int ft_tok_dquo(t_list *token, int i, t_data *data)
{
    int k;
    int j;
    int h;
    char *tmp;

    k = i + 1;
    j = 0;
    h = 0;
    ft_help_dquo(token, data, i);
    tmp = malloc(sizeof(char) * ft_strlen(token->word) - 1);
    if (!tmp)
        return (1);
    while (token->word[k] != '\"')
        k++;
    while (token->word[j])
    {
        if (j == (i) || j == k)
            j++;
        tmp[h] = token->word[j];
        h++;
        j++;
    }
    tmp[h] = '\0';
    free(token->word);
    token->word = tmp;
    return (0);
}


int ft_tok_quo(t_list *token, int i, int *k)
{
	int j;
	int h;
	char *tmp;
	
	*k = i + 1;
	j = 0;
	h = 0;
	tmp = malloc(sizeof(char) * ft_strlen(token->word) - 1);
	if (!tmp)
		return (1);
	while (token->word[*k] != '\'')
		(*k)++;
	while (token->word[j])
	{
		if (j == (i) || j == *k)
			j++;
		tmp[h] = token->word[j];
		h++;
		j++;
	}
	tmp[h] = '\0';
	free(token->word);
	token->word = tmp;
	return (0);
}



void ft_token_word(t_list *token, t_data *data)
{
	int i;
	int check;
	(void)check;
	
	i = 0;
	check = 0;	
	while (token->word[i])
	{
        data->breakpoint = i;
        if (token->word[0] == '~')
            check = ft_tilda(token, data);
		if (token->word[i] == '\'')
            check = ft_tok_quo(token,  data->breakpoint, &i);
		if (token->word[i] == '\"')
        check = ft_tok_dquo(token,  data->breakpoint, data);
		if (token->word[i] == '$')
        {
            ft_tok_dollar(token, data->breakpoint, data);
            i = i - 1;
        }
		i++;
	}
	data->breakpoint = 0;
}


void ft_treatmen_token(t_data *data)
{
	t_list *tmp;
	
	tmp = data->token;	
	while (tmp != NULL)
	{		
			if (tmp->word[0] == '|')
            {
                tmp->value = 'P';
                g_exit = 0;
            }
				
			else if (tmp->word[0] == '<' || tmp->word[0] == '>' 
			|| (tmp->word[1] && tmp->word[1] == '<') 
			|| (tmp->word[1] && tmp->word[1] == '>'))
				tmp->value = 'R';
			else
			   {
				   tmp->value = 'W';
				   ft_token_word(tmp, data);
			   }
			tmp = tmp->next;
	}
	ft_token_red_treat(data->token);
	data->breakpoint = 0;
}
