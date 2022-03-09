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
//	 	printf("%d", ft_len_for_pipe(data->token, p));
		des = info_new();
		k = 0;
	 	i = 0;
		des->command = ft_strdup(tmp->word);
		des->arg = malloc(sizeof(char **) * ft_len_for_pipe(data->token, p) + 1);
		des->red = malloc(sizeof(char **) * ft_len_for_pipe2(data->token, p) * 2 + 1);
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
                    if (ft_strcmp(tmp->word, "4") == 0)
                    {
                        ft_filling_red(des, tmp->next->word);
                        des->red[k] = ft_strdup("2");
                        des->red[k + 1] = ft_strdup(ft_strjoin("herdoc_", ft_itoa(p)));
                        
                    }
                    else
                    {
                        des->red[k] = ft_strdup(tmp->word);
                        des->red[k + 1] = ft_strdup(tmp->next->word);
                    }
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
         //ft_lstprint_content(&des->redir);
		des = des->next;
		p++;
		//free token
	}
	//info_print_content(&data->info);
	//printf("%s", data->info->arg[0]);
	//printf("%s", des->command);
	//ft_lstprint_content(&data->token);
//    ft_filling_red(data->info, "123");
//    ft_lstprint_content(&data->info->redir);

}

