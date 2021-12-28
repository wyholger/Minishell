#include "../include/minishell.h"









//void ft_init_struct_info(t_info *info)
//{
//    //info->command = NULL;
//    //info->arg = NULL;
//    //info->flag = NULL;
//    //info->info = NULL;
//    //info->pipe = 0;
//}

void ft_init_struct_data(t_data *data, char **envp)
{
    data->envp = envp;
    data->exit_proc_number = 0;
    //data->str = str;
    data->token = NULL;
    data->first_elem_info = NULL;

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

//void ft_token_red_treat(t_list *token)
//{
//    int i;
//
//    i = 0;
//
//}

int ft_it_is_key(t_list *token, char *str, t_data *data)
{
    char *tmp;
    int i;
    int k;
    int h;
    
    k = 0;
    i = 0;
    h = 0;
    tmp = malloc(sizeof(char) * ft_strlen(token->word) + ft_strlen(str));
    while (token->word[i] != '$')
        i++;
    while (token->word[k] != '\0')
    {
        if (k == i)
        {
            i = 0;
            while (str[i] != '\0')
            {
                tmp[h] = str[i];
                i++;
                h++;
            }
            k = data->breakpoint;
            data->breakpoint = h;
        }
        tmp[h] = token->word[k];
        k++;
        h++;
    }
   
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


int ft_dollar(t_list *token, char *str, t_data *data)
{
    char *tmp;

    tmp = search_in_envp(data, str);
    if (tmp != NULL)
        ft_it_is_key(token, tmp, data);
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


int ft_tok_dollar(t_list *token, int *i, t_data *data)
{
    int k;
    int j;
    char *tmp;
    
    k = 0;
    j = *i + 1;
    while (token->word[j] != '\0' && token->word[j] != '\\' && token->word[j] != '\'' && token->word[j] != '\"' && token->word[j] != '$' )
        j++;
    tmp = malloc(sizeof(char) * (j - *i));
    if (!tmp)
        return (1);
    *i = *i + 1;
    while ((*i) != j)
    {
        tmp[k] = token->word[(*i)];
        k++;
        (*i)++;
    }
    tmp[k] = '\0';
    //printf("%s\n", tmp);
    data->breakpoint = j;
    ft_dollar(token, tmp, data);
    *i = data->breakpoint;
    //free
    token = NULL;
    
    return (0);
}


int ft_tok_slash(t_list *token, int *i)
{
    int j;
    int h;
    char *tmp;

    j = 0;
    h = 0;
    tmp = malloc(sizeof(char) * ft_strlen(token->word));
    if (!tmp)
        return (1);
    if (!token->word[(*i) +1])
        return(1);
    while (token->word[j])
    {
        if (j == (*i))
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


int ft_tok_quo(t_list *token, int *i)
{
    int k;
    int j;
    int h;
    char *tmp;
    
    k = *i + 1;
    j = 0;
    h = 0;
    tmp = malloc(sizeof(char) * ft_strlen(token->word) - 1);
    if (!tmp)
        return (1);
    while (token->word[k] != '\'')
        k++;
    while (token->word[j])
    {
        if (j == (*i) || j == k)
            j++;
        tmp[h] = token->word[j];
        h++;
        j++;
    }
    tmp[h] = '\0';
    free(token->word);
    token->word = tmp;
    *i = k - 1;
    return (0);
}

void ft_token_word(t_list *token, t_data *data)
{
    int i;
    int check;
    
    i = 0;
    check = 0;
    
    while (token->word[i])
    {
        if (token->word[i] == '\'')
         check = ft_tok_quo(token,  &i);
        //if (token->word[i] == '\"')
         //check = ft_tok_dquo(token,  &i);
        if (token->word[i] == '\\')
         check = ft_tok_slash(token,  &i);
        if (token->word[i] == '$')
         check = ft_tok_dollar(token,  &i, data);
        i++;
    }
    data->breakpoint = 0;
}

void ft_treatmen_token(t_data *data)
{
    printf("Check\n");
    t_list *tmp;
    
    tmp = data->token;
    
    while (tmp != NULL)
    {
            if (tmp->word[0] == ';')
                tmp->value = 'S';
            if (tmp->word[0] == '|')
                tmp->value = 'P';
            else
               ft_token_word(tmp, data);
            tmp = tmp->next;
    }
    ft_lstprint_content(&data->token);
    printf("Check\n");
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
    data->breakpoint = *i;
    return (ft_lstnew(new_token->word));
}

t_list *ft_token_semocolon(t_data *data, int *i)
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
    data->breakpoint = *i;
    return (ft_lstnew(new_token->word));
}

t_list *ft_token_spec(t_data *data, int *i)
{
    int k;
    int j;
    t_list *new_token;
    
    j  = 0;
    k = data->breakpoint;
    new_token = malloc(sizeof(t_list));
    new_token->word = malloc(sizeof(char) * 2);
    if(!new_token->word || !new_token)
        return(NULL);
        new_token->word[0] = data->str[k];
    
    new_token->word[1] = '\0';
    data->breakpoint = *i + 1;
    return (ft_lstnew(new_token->word));
}

void ft_pars_token(t_data *data)
{
    int i;
    t_list *tmp;
    tmp = data->token;
    data->breakpoint = 0;
    i = 0;
    while (data->str[i])
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
        if (data->str[i] == ';')
        {
			ft_lstadd_back(&data->token, ft_token_semocolon(data, &i));
            ft_lstadd_back(&data->token, ft_token_spec(data, &i));
        }
        if (data->str[i] == '|')
        {
            ft_lstadd_back(&data->token, ft_token_pipe(data, &i));
            ft_lstadd_back(&data->token, ft_token_spec(data, &i));
        }
        i++;
    }
    //ft_lstprint_content(&data->token);
}


void ft_parser(t_data *data, char **envp)
{
    int check;
    
    check = 0;
    ft_init_struct_data(data, envp);
    printf("%s\n", data->str);
    check = ft_check_all_string(data);
    if (check == 0)
    {

        ft_pars_token(data);
        ft_treatmen_token(data);
          // send struct
    }
        
   else
       printf("Error\n");
  
    ft_lstclear(&data->token);
    
    
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_data data;
    
    data.str = "H'el  lo W>e'  Test$USERing$USER r$USER|r<  $? $USER  'dd>y'  ;     World ";
    ft_parser(&data, envp);
    
}
