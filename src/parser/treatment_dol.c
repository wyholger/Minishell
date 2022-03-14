#include "../../include/minishell.h"

int ft_alpha_help(t_list *token)
{
    int i;
    int j;
    
    j = 0;
    i = 0;
    while (token->word[i] != '$')
        i++;
    j = i + 1;
    while (token->word[j] != '\0' && token->word[j] != '\'' && token->word[j] != '\"' && token->word[j] != '$')
    j++;
    return (j - i);
}

int ft_it_is_key(t_list *token, char *str, int i, int k)
{
    char *tmp;
    int h;
    int n;
    
    n = 0;
    h = 0;
    tmp = malloc(sizeof(char) * ft_strlen(token->word) + ft_strlen(str));
    if (!tmp)
        return (1);
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
            k = k + ft_alpha_help(token);
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

char *ft_fil_dol_ex(t_list *token, char *tmp, char *str, int i)
{
    int k;
    int h;
    
    h = 0;
    k = 0;
    while (token->word[i] != '$')
        i++;
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
    return(tmp);
}

int ft_dollar_exit(t_list *token, t_data *data)
{
    
    char *tmp;
    char *str;
    
    if (g_exit != 0)
    {
        str = ft_itoa(g_exit);
        data->exit_proc_number = 0;
    }
    else
        str = ft_itoa(data->exit_proc_number);
    tmp = malloc(sizeof(char) * strlen(token->word) + ft_strlen(str) - 1);
    if (!tmp)
        return (1);
    ft_fil_dol_ex(token, tmp, str, 0);
    free(token->word);
    free(str);
    token->word = tmp;
    return (0);
}




int ft_dollar_alpha(t_list * token, int j)
{
    int i;
    int k;
    char *tmp;

    i = 0;
    while (token->word[i] != '$')
        i++;
    k = i;
    while (token->word[i] != '\0')
        i++;
    tmp = malloc(sizeof(char) * i - ft_alpha_help(token));
    if (!tmp)
        return (1);
    i = 0;
    while (token->word[i] != '\0')
    {
        if (i == k)
            i = i + ft_alpha_help(token);
        tmp[j] = token->word[i];
        i++;
        j++;
    }
    tmp[j] = '\0';
    free(token->word);
    token->word = tmp;
    return (0);
}


int ft_dollar(t_list *token, char *str, t_data *data)
{
    char *tmp;

    tmp = search_in_envp(data, str);
    if (tmp != NULL)
    {
        ft_it_is_key(token, tmp, 0, 0);
        free(tmp);
    }
    else
    {
            if (ft_isalpha(str[0]) == 1)
                ft_dollar_alpha(token, 0);
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
    tmp = malloc(sizeof(char) * (j - i) + 1);
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
    ft_dollar(token, tmp, data);
    free(tmp);
    return (0);
}
