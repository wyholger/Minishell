#include "minishell.h"
#include "libft.h"


void ft_init_struct_info(t_info *info)
{
    //info->command = NULL;
    //info->arg = NULL;
    //info->flag = NULL;
    //info->info = NULL;
    //info->pipe = 0;
}


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
        if(data->str[j] == '\'')
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
        if(data->str[j] == '\"')
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
    while(data->str[i])
    {
        if(data->str[i] == '\'')
            check = ft_cansel_quote(data, &i);
        if(data->str[i] == '\"')
            check = ft_cansel_double_quote(data, &i);
        if (check == 1)
            return (check);
        i++;
    }
    if(data->str[i - 1] == '|')
        check = 1;
    if(data->str[i - 1] == '<' || data->str[i - 1] == '>')
       check = 1;
    return (check);
}


void ft_pars_token(t_data *data)
{
    
    
}


void ft_parser(t_data *data, char **envp)
{
    int check;
    
    check = 0;
    ft_init_struct_main(data, envp);
    printf("%s\n", data->str);
    check = ft_check_all_string(data);
    if (check == 0)
    {
        printf("%s\n", data->str);
        ft_pars_token(data);
    }
        
   else
       printf("Error\n");
    //printf("%s\n", main->str_for_semocolon);
    // send struct
    
    
    
}


int main(int argc, char **argv, char **envp)
{
    t_data data;
    
    //char *str = "Hello W  lol orld  W'erry";
    data.str = "Hello W  \"lo'l orld\"  W'er'ry";
    //printf("%s\n", data.str);
    ft_parser(&data, envp);
    
}
