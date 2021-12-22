#include "minishell.h"
#include "libft.h"


void ft_init_struct_info(t_info *info)
{
    info->command = NULL;
    info->arg = NULL;
    info->flag = NULL;
    info->info = NULL;
    info->pipe = 0;
}


void ft_init_struct_main(t_main *main, char **env, char *str)
{
    main->env = env;
    main->exit_proc_number = 0;
    main->str = str;
    main->arg_per_one = NULL;
}

char *ft_new_str_parse(t_main *main, int *i, int *j)
{
    char *tmp;
    int k;
    int h;
    
    k = 0;
    h = 0;
    tmp = malloc(sizeof(char) * ft_strlen(main->str) - 1);
    if (!tmp)
        return (NULL);
    while (main->str[k])
    {
        if (k == *i || k == *j)
            k++;
        tmp[h] = main->str[k];
        k++;
        h++;
    }
    tmp[h] = '\0';
    //free(main->str);
    main->str = tmp;
    return(main->str);
    
}

int ft_it_is_key(char *str, t_main *main)
{
    int i;
    
    i = 0;
    
    
    
    return(0);
}


int ft_dollar(t_main *main, int *i)
{
    int j;
    char *tmp;
    int k;
    
    k = 0;
    j = *i++;
    while (main->str[j] != ' ')
        j++;
    tmp = malloc(sizeof(char) * (j - *i));
    j = *i++;
    while (main->str[j] != ' ')
    {
        tmp[k] = main->str[j];
        k++;
        j++;
    }
    tmp[k] = '\0';
    k = ft_it_is_key(tmp, main);
    
    return(0);
}

void ft_new_str(t_main *main, int *i)
{
    int k;
    int j;
    char *tmp;
    
    j = *i;
    k = 0;
    while (main->str[j] != ';' && main->str[j] != '\0')
        j++;
    tmp = malloc(sizeof(char) * (j - *i) + 1);
    j = *i;
    while (main->str[j] != ';' && main->str[j] != '\0')
    {
        tmp[k] = main->str[j];
        k++;
        j++;
    }
    tmp[k] = '\0';
    //free main->str
    main->str = tmp;
    free(tmp);
    *i = 0;
}

int ft_backslash(t_main *main, int *i)
{
    int j;
    
    j = *i;
    ft_new_str_parse(main, i, &j);
    return(0);
}

int ft_cansel_quote(char *str, int *i)
{
    int j;
    
    j = *i;
    while (str[++j])
    {
        if(str[j] == '\'')
            return (0);
    }
    return (1);
}

int ft_cansel_double_quote(char *str, int *i)
{
    int j;
    
    j = *i;
    while (str[++j])
    {
        if(str[j] == '\"')
            return (0);
    }
    return (1);
}


int ft_quoetes(t_main *main, int *i)
{
    int j;
    int check;
    
    check = 0;
    j = *i;
    check = ft_cansel_quote(main->str, i);
    if (check == 0)
    {
        while(main->str[++(*i)] != '\'')
        {
            //if(main->str[*i] == '\')
               //ft_new_str_parse_backslash(main, i, &j);
            if(main->str[*i] == '\'')
                break ;
        }
        ft_new_str_parse(main, i, &j);
    }
    
    
    
    
    
    return(check);
}

int ft_double_quoetes(t_main *main, int *i)
{
    int j;
    int check;
    
    check = 0;
    j = *i;
    check = ft_cansel_double_quote(main->str, i);
    if (check == 0)
    {
        while(main->str[++(*i)] != '\"' && main->str[++(*i)] != '\0')
        {
            //if(main->str[*i] == '\')
               //ft_new_str_parse_backslash(main, i, &j);
            //if(main->str[*i] == '$')
            //ft_dollar(main, i, &j);
        }
        ft_new_str_parse(main, i, &j);
    }
    
    return(check);
}



int ft_pipe(t_main *main, int *i, t_info *info)
{
    int k;
    char *tmp;
    
    k = *i;
    tmp = malloc(sizeof(char) * (k + 1));
    k = 0;
    while (k != *i)
    {
        tmp[k] = main->str[k];
        k++;
    }
    tmp[k] = '\0';
    main->str_for_semocolon = tmp;
    free(tmp);
    *i = *i + 1;
    return(0);
}



int ft_semocolon(t_main *main, int *i, t_info *info)
{
    
    
    return(0);
}



int ft_pars_all_string(t_main *main, t_info *info)
{
    int i;
    int check;
    
    check = 0;
    i = 0;
    while(main->str[i])
    {
        if(main->str[i] == '\'')
            check = ft_quoetes(main, &i);
        if(main->str[i] == '\"')
            check = ft_double_quoetes(main, &i);
        if(main->str[i] == '$')
            check = ft_dollar(main, &i);
        if(main->str[i] == '\\')
            check = ft_backslash(main, &i);
        if(main->str[i] == '|')
            check = ft_pipe(main, &i, info);
        if(data->str[i] == '<' || data->str[i] == '>' || data->str[i] == '<<' || data->str[i] == '>>)
           check = ft_redirects(data, &i);
        if(main->str[i] == ';')
        {
            ft_semocolon(main, &i, info);
            ft_new_str(main, &i);
            return (check);
        }
        if (check == 1)
            return (check);
        i++;
    }
    return (check);
}

void ft_parser(char *str, char **env)
{
    t_main *main;
    t_info *info;
    int i = 0;
    int check;
    
    check = 0;
    //if (main == NULL || info == NULL)
      //  check = 1;
    ft_init_struct_main(main, env, str);
    ft_init_struct_info(info);
    printf("%s\n", main->str);
    check = ft_pars_all_string(main, info);
    if (check == 0)
        printf("%s\n", main->str);
   else
       printf("Error\n");
    printf("%s\n", main->str_for_semocolon);
    // send struct
    
    
    
}


int main(int argc, char **argv, char **env)
{
    
    char *str = "Hello W  lol orld  W'erry";
    ft_parser(str, env);
    
}
