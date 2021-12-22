#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    t_data data;

	//ft_init_struct(&data, envp);
    while (data.status != 0)
    {
        printf("minishell$ ");
        //ft_read_line
        //ft_parser
        
    }
    //free struct
}
