#include "../../include/minishell.h"


int ft_len_for_pipe2(t_list *token, int i)
{
    int k;

    k = 0;
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

    k = 0;
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


void ft_filling_red(t_info *info, char *des)
{
    char *str;
    
    if (info->redir != NULL)
        ft_lstclear(&info->redir);
    while (1)
    {
        str = readline("> ");
        if (ft_strcmp(str, des) == 0)
            break ;
        ft_lstadd_back(&info->redir, ft_lstnew(str));
        free(str);
    }
    free(str);
    
}

char    *generate_heredoke_name(int p)
{
    char    *for_itoa;
    char    *name;

    for_itoa = ft_itoa(p);
    name = ft_strjoin("herdoc_", for_itoa);
    free (for_itoa);
    return (name);
}

void    init_heredok(t_info *des)
{
    int    file;
    t_list    *tmp;

    tmp = des->redir;
    if (des->name_her != NULL)
    {
        file = open(des->name_her, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        while(tmp)
        {
            write (file, tmp->word, ft_strlen(tmp->word));
            write (file, "\n", 1);
            tmp = tmp->next;
        }
        close(file);
    }
}
