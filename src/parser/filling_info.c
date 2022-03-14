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

char	*generate_heredoke_name(int p)
{
	char	*for_itoa;
	char	*name;

	for_itoa = ft_itoa(p);
	name = ft_strjoin("herdoc_", for_itoa);
	free (for_itoa);
	return (name);
}

void	init_heredok(t_info *des)
{
	int	file;
	t_list	*tmp;

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
		ft_lstclear(&des->redir);
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
		if(ft_check_redmal(data->token, p) == 1)
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
						des->name_her = generate_heredoke_name(p);
						des->red[k + 1] = ft_strdup(des->name_her);
						
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
		if(ft_check_redmal(data->token, p) == 1)
		{
			des->red[k] = NULL;
			if (des->red[0] == NULL)
				des->red = NULL;
		}
			
		info_add_back(&data->info, des);
		if (tmp != NULL)
		tmp = tmp->next;
		 //ft_lstprint_content(&des->redir);
		 //вот тут можно вызвать функцию для создания файла;
		init_heredok(des);
		des = des->next;
		p++;
	}
	// info_print_content(&data->info);
	//printf("%s", data->info->arg[0]);
	//printf("%s", des->command);
	//ft_lstprint_content(&data->token);
//    ft_filling_red(data->info, "123");
//    ft_lstprint_content(&data->info->redir);

}

