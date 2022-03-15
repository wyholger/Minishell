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

int ft_check_redmal(t_list *token, int i)
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
            return (1);
        token = token->next;
    }
    return (0);
}


















void ft_fill_comm(t_info *des, int p, t_data *data)
{
    t_list *tmp;
    
    tmp = data->token;
    while (p != 0)
    {
        while (tmp && tmp->value != 'P')
            tmp = tmp->next;
        if (tmp->next)
            tmp = tmp->next;
        p--;
    }
    des->command = ft_strdup(tmp->word);
    des->arg[0] = ft_strdup(tmp->word);
    des->arg[1] = NULL;
}

void ft_des_mal(t_info *des, int p, t_data *data)
{
    des->arg = malloc(sizeof(char **) * ft_len_for_pipe(data->token, p) + 1);
    if(ft_check_redmal(data->token, p) == 1)
        des->red = malloc(sizeof(char **) * ft_len_for_pipe2(data->token, p) * 2 + 1);
}


int ft_fil_fl(t_info *des, t_data *data, int p)
{
    t_list *tmp;
    int k;
    
    k = 0;
    tmp = data->token;
    while (p != 0)
    {
        while (tmp && tmp->value != 'P')
            tmp = tmp->next;
        if (tmp->next)
            tmp = tmp->next;
        p--;
    }
    if (tmp->next)
        tmp = tmp->next;
    if (ft_strcmp(tmp->word, "-n") == 0)
        des->flag = 1;
    if (tmp->next)
    {
        while (tmp->next && ft_strcmp(tmp->word, "-n") == 0)
        {   tmp = tmp->next;
            k++;
        }
    }
    if (des->flag == 1 && k == 0)
        return (1);
    return (k);
}

void ft_red_fil(t_list *tmp, t_list *tmp1, t_info *des, int *k)
{
    if (ft_strcmp(tmp->word, "4") == 0)
    {
        ft_filling_red(des, tmp1->word);
        des->red[*(k)] = ft_strdup("2");
        des->red[*(k) + 1] = ft_strdup(des->name_her);
    }
    else
    {
        des->red[*(k)] = ft_strdup(tmp->word);
        des->red[*(k) + 1] = ft_strdup(tmp1->word);
    }
    *(k) = *(k) + 2;
}


void ft_fill_arg1(t_info *des, t_list *tmp, int p, int z)
{
    int i;
    int k;
    
    i = 1;
    k = 0;
    while (tmp && tmp->value != 'P')
    {
        if (tmp->value == 'W' && ft_strcmp(tmp->word, "-n") != 0)
        {
            des->arg[i] = ft_strdup(tmp->word);
            i++;
        }
        if (tmp->value == 'R')
        {
            if (ft_strcmp(tmp->word, "4") == 0)
                des->name_her = generate_heredoke_name(p);
            ft_red_fil(tmp, tmp->next, des, &k);
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    if (tmp && tmp->value == 'P')
        des->pipe = 1;
    des->arg[i] = NULL;
        if (z == 1)
    des->red[k] = NULL;
}

void ft_fill_arg(t_info *des, t_data *data, int p)
{
    t_list *tmp;
    int k;
    
    tmp = data->token;
    while (p != 0)
    {
        while (tmp && tmp->value != 'P')
            tmp = tmp->next;
        if (tmp->next && tmp->value == 'P')
            tmp = tmp->next;
        p--;
    }
    if (tmp->next)
        tmp = tmp->next;
    k = ft_fil_fl(des, data, p);
    while (tmp->next && k != 0)
    {
        tmp = tmp->next;
        k--;
    }    
    if(ft_check_redmal(data->token, p) == 1)
        ft_fill_arg1(des, tmp, p, 1);
    else
        ft_fill_arg1(des, tmp, p, 0);
}


void ft_filling_info(t_data * data, int p)
{
    t_info *des;
    t_list *tmp;

    tmp = data->token;
    des = data->info;
    while (tmp != NULL)
    {
        des = info_new();
        ft_des_mal(des, p, data);
        ft_fill_comm(des, p, data);
        if (tmp->next)
        {
            tmp = tmp->next;
            ft_fill_arg(des, data, p);
        }        
        while (tmp && tmp->value != 'P')
            tmp = tmp->next;
        info_add_back(&data->info, des);
        if (tmp != NULL)
            tmp = tmp->next;
        init_heredok(des);
        des = des->next;
        p++;
    }
   // info_print_content(&data->info);
}
