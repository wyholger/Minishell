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
}

void	ft_init_struct(t_data *data, char **envp)
{
	(void)envp;
	data->status = 1;
	data->first_elem = NULL;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
    t_data data;

	ft_init_struct(&data, envp);
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
