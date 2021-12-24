#include "../include/minishell.h"

//void ft_init_struct_info(t_info *info)
//{
//    //info->command = NULL;
//    //info->arg = NULL;
//    //info->flag = NULL;
//    //info->info = NULL;
//    //info->pipe = 0;
//}

void ft_init_struct_main(t_data *data, char **envp)
{
    data->envp = envp;
    data->exit_proc_number = 0;
    //data->str = str;

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


//void ft_treatmen_token(t_list *token)
//{
//
//}


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
    printf("%s\n", new_token->word);
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
    new_token->word = malloc(sizeof(char) * (*i - k) + 2);
    if(!new_token->word || !new_token)
        return(NULL);
    while (k != (*i + 1))
    {
        new_token->word[j] = data->str[k];
        k++;
        j++;
    }
    new_token->word[j] = '\0';
    data->breakpoint = *i + 1;
    printf("%s\n", new_token->word);
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
    new_token->word = malloc(sizeof(char) * (*i - k) + 2);
    if(!new_token->word || !new_token)
        return(NULL);
    while (k != (*i + 1))
    {
        new_token->word[j] = data->str[k];
        k++;
        j++;
    }
    new_token->word[j] = '\0';
    data->breakpoint = *i + 1;
//    printf("%s\n", new_token->word);
    return (ft_lstnew(new_token->word));
}


void ft_pars_token(t_data *data, t_list *token)
{
    int i;
    t_list *tmp;
    
    tmp = NULL;
    data->breakpoint = 0;
    i = 0;
    while (data->str[i])
    {
        if (data->str[i] == '\'')
            ft_quotes(data, &i, token);
        if (data->str[i] == '\"')
            ft_double_quotes(data, &i, token);
        if (data->str[i] == ' ')
        {
            tmp = ft_token_space(data, &i);
            ft_lstadd_back(&token, tmp);  //первый аргумент должен быть зануленным при первом проходе, чтобы функция его распознала как начало
//            ft_lstadd_front(&token, tmp);
        }
        if (data->str[i] == ';')
        {
            tmp = ft_token_semocolon(data, &i);
			ft_lstadd_back(&token, tmp);
//            ft_lstadd_front(&token, tmp);
        }
        if (data->str[i] == '|')
        {
            tmp = ft_token_pipe(data, &i);
            ft_lstadd_back(&token, tmp);
//            ft_lstadd_front(&token, tmp);
        }
            
        i++;
    }
    //Надо посмотреть как делается список;
    ft_lstprint_content(&token);
    
}


void ft_parser(t_data *data, char **envp)
{
    int check;
    t_list token;
    
    check = 0;
    ft_init_struct_main(data, envp);
    printf("%s\n", data->str);
    check = ft_check_all_string(data);
    if (check == 0)
    {
//        printf("%s\n", data->str);
        ft_pars_token(data, &token);
          // send struct
    }
        
   else
       printf("Error\n");
  
    
    
    
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_data data;
    
    //char *str = "Hello W  lol orld  W'erry";
    data.str = "He'l  lo'We r|r     ddy;World ";
    //printf("%s\n", data.str);
    ft_parser(&data, envp);
    
}
