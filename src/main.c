#include "../include/minishell.h"

void split_str(t_data *data)
{
	char **for_split;
	int	i;
	
	i = 0;
	for_split = ft_split(data->str, ' ');
	while (for_split[i])
	{
		ft_lstadd_back(&data->first_elem, ft_lstnew(for_split[i]));
		i++;
	}
	ft_lstprint_content(&data->first_elem);
	ft_lstclear(&data->first_elem);
	split_free(for_split);
}

void	ft_init_struct(t_data *data, char **envp)
{
	(void)envp;
	data->status = 1;
	data->first_elem = NULL;
	data->first_elem_info = NULL;
	data->envp = envp;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
    t_data data;
	char *str;
	
	ft_init_struct(&data, envp);
	str = search_in_envp(&data, "PATH");
	printf("%s\n", str);
	free(str);
	while (data.status != 0)
    {
		data.str = readline(MINISHELL_MSG);
		split_str(&data);
		//ft_read_line
		//ft_parser
        free(data.str);
    }
    //free struct
}
