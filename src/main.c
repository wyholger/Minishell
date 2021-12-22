#include "../include/minishell.h"

void	ft_init_struct(t_data *data, char **envp)
{
	(void)envp;
	data->status = 1;
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
		data.str = readline("minishell$ ");
        //ft_read_line
        //ft_parser
        
    }
    //free struct
}
