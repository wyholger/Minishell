#include "../include/minishell.h"


int ft_len_for_pipe2(t_list *token, int i)
{
	int k;

	k = 0;
	// while(k != i)
	// {
	// 	token = token->next;
	// 	k++;
	// }
	// if (token->value == 'P')
	// 	token = token->next;
	while (token != NULL && i != 0)
	{
		if (token->value == 'P')
			i--;
		token = token->next;
	}
	if (token != NULL && token->value == 'P')
		token = token->next;
	while (token != NULL && token->value != 'P')
	{
		if (token->value == 'R')
		{
			k++;
		}
		token = token->next;
	}
	return (k);
}


int ft_len_for_pipe(t_list *token, int i)
{
	int k;
	//int p;

	k = 0;
	// while(k != i)
	// {
	// 	token = token->next;
	// 	k++;
	// }
	// if (token->value == 'P')
	// 	token = token->next;
	// k = 0;
	while (token != NULL && i != 0)
	{
		if (token->value == 'P')
			i--;
		token = token->next;
	}
	if (token != NULL && token->value == 'P')
		token = token->next;
	while (token != NULL && token->value != 'P')
	{
		if (token->value == 'W')
		{
			k++;
		}
		token = token->next;
	}
	return (k);
}


void ft_filling_info(t_data *data)
{
	t_list *tmp;
	t_info *des;
	int i;
	int k;
	int check;
	int p;
	des = data->info;	
	tmp = data->token;
	check = 0;
	p = 0;
	while (tmp != NULL)
	 {
	 	printf("%d", ft_len_for_pipe(data->token, p));
		des = info_new();
		k = 0;
	 	i = 0;
		des->command = ft_strdup(tmp->word);
		des->arg = malloc(sizeof(char **) * ft_len_for_pipe(data->token, p));
		des->red = malloc(sizeof(char **) * ft_len_for_pipe2(data->token, p) * 2);		
		des->arg[i] = ft_strdup(tmp->word);
			i++;
		if (tmp->next)
		{
			tmp = tmp->next;
			check = 1;
		}		
		if (ft_strcmp(tmp->word, "-n") == 0)
			des->flag = 1;
		if (tmp->next)
		{
			while (ft_strcmp(tmp->word, "-n") == 0)
					tmp = tmp->next;
		}		
		while (tmp != NULL && tmp->value != 'P' && check == 1)
		{
			if (tmp->value == 'W')
				{
					des->arg[i] = ft_strdup(tmp->word);
		 			i++;
				}
			if (tmp->value == 'R')
				{
					des->red[k] = ft_strdup(tmp->word);
					des->red[k + 1] = ft_strdup(tmp->next->word);
		 			k = k + 2;
					tmp = tmp->next;
				}
				tmp = tmp->next;			
		}
		if (tmp && tmp->value == 'P')
			des->pipe = 1;
		des->arg[i] = NULL;
		des->red[k] = NULL;
		if (des->red[0] == NULL)
			des->red = NULL;
		info_add_back(&data->info, des);
		if (tmp != NULL)
		tmp = tmp->next;
		des = des->next;
		p++;
		//free token
	}
	//info_print_content(&data->info);
	//printf("%s", data->info->arg[0]);
	//printf("%s", des->command);
	//ft_lstprint_content(&data->token);

}

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


void ft_red_new(t_list *token, int i)
{
	char *tmp;

	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return ;
	if (i == 1)
		tmp[0] = '1';
	if (i == 2)
		tmp[0] = '2';
	if (i == 3)
		tmp[0] = '3';
	if (i == 4)
		tmp[0] = '4';
	if (i == 5)
		tmp[0] = '5';
	if (i == 6)
		tmp[0] = '6';
	tmp[1] = '\0';
	free(token->word);
	token->word = tmp;
}


void ft_token_red_treat(t_list *token)
{
   t_list *tmp;

   tmp = token;

   while (tmp)
   {
	   if (tmp->value == 'R')
	   {
		   	if (tmp->word[0] == '<' && !tmp->word[1])
			   ft_red_new(tmp, 2);
			if (tmp->word[0] == '>' && !tmp->word[1])
			   ft_red_new(tmp, 1);
			if (tmp->word[0] == '<' && tmp->word[1] && tmp->word[1] == '<')
			   ft_red_new(tmp, 4);
			if (tmp->word[0] == '>' && tmp->word[1] && tmp->word[1] == '>')
			   ft_red_new(tmp, 3);
			if (tmp->word[0] == '2' && tmp->word[1] && tmp->word[1] == '>'
			&& !tmp->word[2])
			   ft_red_new(tmp, 5);
			if (tmp->word[0] == '2' && tmp->word[1] && tmp->word[1] == '>'
			&& tmp->word[2] && tmp->word[2] == '>')
			   ft_red_new(tmp, 6);
	   }
	   tmp = tmp->next;
   }

}

int ft_it_is_key(t_list *token, char *str, t_data *data, int j)
{
	char *tmp;
	int i;
	int k;
	int h;
    int n;
    
    
    n = 0;
	k = 0;
	i = 0;
	h = 0;
	tmp = malloc(sizeof(char) * ft_strlen(token->word) + ft_strlen(str));
    //if (!tmp)
        //return (1);
	while (token->word[i] != '$')
		i++;
	while (token->word[k] != '\0')
	{
		if (k == i)
		{
			while (str[n] != '\0')
			{
				tmp[h] = str[n];
				n++;
				h++;
			}
			k = j;
			data->breakpoint = h;
		}
		tmp[h] = token->word[k];
		k++;
		h++;
	}
    //h = data->breakpoint;
	free(token->word);
	token->word = tmp;
	return (0);
}

int ft_dollar_digit(t_list *token, t_data *data)
{
	int i;
	char *tmp;
	int k;
	int h;
	
	i = 0;
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

int ft_dollar_exit(t_list *token, t_data *data)
{
	// Сделать функцию чтобы убрать тут одну переменную!!!
	int i;
	char *tmp;
	int k;
	char *str;
	int h;
	
	i = 0;
	k = 0;
	h = 0;
	str = ft_itoa(data->exit_proc_number);
	tmp = malloc(sizeof(char) * strlen(token->word) + ft_strlen(str) - 1);
	if (!tmp)
		return (1);
	while (token->word[i] != '$')
		i++;
	data->breakpoint = i;
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
	free(token->word);
	token->word = tmp;
	return (0);
}

int ft_dollar_alpha(t_data *data, t_list * token)
{
	int i;
	int k;
	char *tmp;
	int h;
	
	i = 0;
	while (token->word[i] != '$')
		i++;
	k = data->breakpoint;
	while (token->word[k] != '\0')
	{
		i++;
		k++;
	}
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		return (1);
	i = 0;
	k = 0;
	while (token->word[k] != '\0')
	{
		if (token->word[k] == '$' && k < data->breakpoint)
		{
			h = k;
			k = data->breakpoint;
			data->breakpoint = h - 1;
		}
		tmp[i] = token->word[k];
		i++;
		k++;
	}
	tmp[i] = '\0';
	free(token->word);
	token->word = tmp;
	return (0);
}


int ft_dollar(t_list *token, char *str, t_data *data, int i)
{
	char *tmp;

	tmp = search_in_envp(data, str);
	if (tmp != NULL)
		 ft_it_is_key(token, tmp, data, i);
	else
	{
			if (ft_isalpha(str[0]) == 1)
				ft_dollar_alpha(data, token);
			else if (ft_isdigit(str[0]) == 1)
				ft_dollar_digit(token, data);
			else if (str[0] == '?')
				ft_dollar_exit(token, data);
	}

	return (0);
}


int ft_tok_dollar(t_list *token, int i, t_data *data)
{
	int k;
	int j;
	char *tmp;
	
	k = 0;
	j = i + 1;
	while (token->word[j] != '\0' && token->word[j] != '\'' && token->word[j] != '\"' && token->word[j] != '$')
		j++;
	tmp = malloc(sizeof(char) * (j - i));
	if (!tmp)
		return (1);
	i = i + 1;
	while (i != j)
	{
		tmp[k] = token->word[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
//	printf("%s\n", tmp);
	ft_dollar(token, tmp, data, j);
    //printf("%s\n", tmp);
	//free
	//token = NULL;
	
	return (0);
}

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
    //printf("%d", k);
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


int ft_tok_quo(t_list *token, int i)
{
	int k;
	int j;
	int h;
	char *tmp;
	
	k = i + 1;
	j = 0;
	h = 0;
	tmp = malloc(sizeof(char) * ft_strlen(token->word) - 1);
	if (!tmp)
		return (1);
	while (token->word[k] != '\'')
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

int ft_tilda(t_list *token, t_data *data)
{
    int k;
    char *tmp;
    int i;
    
    k = 0;
    i = 0;
    if (token->word[1] != '\0' && token->word[1] != '/')
        return(1);
    tmp = malloc(sizeof(char) * ft_strlen(token->word) + ft_strlen(data->pwd_home));
    if (!tmp)
        return(1);
    while (data->pwd_home[i])
    {
        tmp[k] = data->pwd_home[i];
        k++;
        i++;
    }
    i = 1;
    while(token->word[i])
    {
       tmp[k] = token->word[i];
        k++;
        i++;
    }
    tmp[k] = '\0';
    free(token->word);
    token->word = tmp;
    return(0);
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
            check = ft_tok_quo(token,  data->breakpoint);
		if (token->word[i] == '\"')
        check = ft_tok_dquo(token,  data->breakpoint, data);
		if (token->word[i] == '$')
        {
            ft_tok_dollar(token, data->breakpoint, data);
        }
		i++;
	}
	data->breakpoint = 0;
}


void ft_treatmen_token(t_data *data)
{
	//printf("Check\n");
	t_list *tmp;
	
	tmp = data->token;
	
	while (tmp != NULL)
	{		
			if (tmp->word[0] == '|')
				tmp->value = 'P';
			else if (tmp->word[0] == '<' || tmp->word[0] == '>' 
			|| (tmp->word[1] && tmp->word[1] == '<') 
			|| (tmp->word[1] && tmp->word[1] == '>'))
				tmp->value = 'R';
			// else if (tmp->word[0] == '\0')
			// 	tmp->value = 'S';
			else
			   {
				   tmp->value = 'W';
				   ft_token_word(tmp, data);
			   }
			tmp = tmp->next;
	}
	ft_token_red_treat(data->token);
	//ft_lstprint_content(&data->token);
	//printf("Check\n");
	ft_filling_info(data);
	data->breakpoint = 0;
}


void ft_quotes(t_data *data, int *i, t_list *token)
{
	(void)token;
	(*i)++;
	while (data->str[*i] != '\'')
		(*i)++;
	(*i)++;
}

void ft_double_quotes(t_data *data, int *i, t_list *token)
{
	(void)token;
	(*i)++;
	while (data->str[*i] != '\"')
		(*i)++;
	(*i)++;
}



t_list *ft_token_space(t_data *data, int *i)
{
	int k;
	int j;
	t_list *new_token;
	
	j  = 0;
	k = data->breakpoint;
	new_token = malloc(sizeof(t_list));
	new_token->word = malloc(sizeof(char) * (*i - k) + 1);
	if(!new_token->word || !new_token)
		return(NULL);
	
	while (k != (*i))
	{
		new_token->word[j] = data->str[k];
		k++;
		j++;
	}
	new_token->word[j] = '\0';
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	return (ft_lstnew(new_token->word));
}


int ft_chek_around_pipe(t_data *data, int i)
{
	if (data->str[i - 1] == ' ' && data->str[i + 1] == ' ' )
		return(1);
	if (data->str[i - 1] != ' ' && data->str[i + 1] == ' ' )
		return(2);
	if (data->str[i - 1] == ' ' && data->str[i + 1] != ' ' )
		return(3);
	return (0);
}

t_list *ft_token_pipe(t_data *data, int *i)
{
	int k;
	int j;
	t_list *new_token;
	
	j  = 0;
	k = data->breakpoint;
	new_token = malloc(sizeof(t_list));
	new_token->word = malloc(sizeof(char) * (*i - k) + 1);
	if(!new_token->word || !new_token)
		return(NULL);
	while (k != (*i))
	{
		new_token->word[j] = data->str[k];
		k++;
		j++;
	}
	new_token->word[j] = '\0';
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	return (ft_lstnew(new_token->word));
}


t_list *ft_token_spec(t_data *data, int *i)
{
	int k;
	t_list *new_token;
	
	k = data->breakpoint;
	new_token = malloc(sizeof(t_list));
	new_token->word = malloc(sizeof(char) * 2);
	if(!new_token->word || !new_token)
	{
		return(NULL);
	}
	new_token->word[0] = data->str[k];
	new_token->word[1] = '\0';
	(*i)++;
	while (data->str[(*i)] == ' ')
			(*i)++;
	data->breakpoint = *i;
	return (ft_lstnew(new_token->word));
}

void ft_pars_token(t_data *data)
{
	int i;
	t_list *tmp;
	int p;
	
	tmp = data->token;
	
	i = 0;
	while (data->str[i] == ' ')
		i++;
	data->breakpoint = i;
	while (data->str[i] != '\0')
	{
		if (data->str[i] == '\'')
			ft_quotes(data, &i, tmp);
		if (data->str[i] == '\"')
			ft_double_quotes(data, &i, tmp);
		if (data->str[i] == ' ')
		{
			ft_lstadd_back(&data->token, ft_token_space(data, &i));
			continue ;
		}
		if (data->str[i] == '|')
		{
			p = ft_chek_around_pipe(data, i);
			//printf("%d\n", p);
			if (p == 0 || p == 2)
			{
				ft_lstadd_back(&data->token, ft_token_pipe(data, &i));
				ft_lstadd_back(&data->token, ft_token_spec(data, &i));
			}
			if (p == 1 || p == 3)
			{
				ft_lstadd_back(&data->token, ft_token_spec(data, &i));
			}			
		}
		i++;
	}
	if(data->str[data->breakpoint] != '\0')
    ft_lstadd_back(&data->token, ft_token_space(data, &i));
	//printf("%c", data->str[data->breakpoint]);
	//ft_lstprint_content(&data->token);
}


void ft_parser(t_data *data)
{
	int check;
	
	check = 0;
	//printf("%s\n", data->str);
	check = ft_check_all_string(data);
	if (check == 0)
	{

		ft_pars_token(data);
		ft_treatmen_token(data);
		info_print_content(&data->info);
		  // send struct
	}
		
   else
	   printf("Error\n");  
	ft_lstclear(&data->token);


	
	
}


