#include "../include/minishell.h"

void	exec(t_data *data)
{
	t_info *tmp;
	pid_t	pid;

	(void)pid;
	tmp = data->info;
	data->pipe_size = init_pipe_size(tmp);
	while (tmp != NULL)
	{
		if (tmp->pipe == 0)
			exec_cmd_one(data, tmp);
		else if (tmp->pipe == 1)
			tmp = exec_pipe_redirect(data, tmp);
		tmp = tmp->next;
	}
}
// echo -nnnnnnnn hi

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data data;
	
	ft_init_struct(&data, envp);
	while (data.status != 0)
	{
        ft_sig_read();
        data.str = 0;
		data.str = readline(MINISHELL_MSG);
        if (data.str == 0)
        {
            printf("\033[1Aminishell$ exit\n");
            rl_clear_history();
            exit(0);
        }
        if (data.str != 0)
        {
			add_history(data.str);
			ft_parser(&data);
			init_pid(&data);
			exec(&data);
			wait_pid(&data);
			info_clear(&data.info);
			data.info = NULL;
			free(data.str);
        }
	}
    rl_clear_history();
    return (0);
}
