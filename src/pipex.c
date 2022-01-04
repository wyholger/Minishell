#include "../include/minishell.h"

// int	init_fileout(t_data *data, t_info *info)
// {

// }

// int	init_filein(t_data *data, t_info *info)
// {

// }

void	child_process(t_data *data, t_info *info)
{
	pid_t	pid;
	int		deskr;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		printf("PIPE ERROR\n");
		exit (0);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		// write (fd[0], info->arg, ft_strlen(info->arg));
		// printf("BLAAAAAAAAA %d\n", fd[0]);
		// write(1, "Y\n", 2);
		// printf("BLAAAAAAAAA %d\n", deskr);
		// if (info->pipe == 1)
		deskr = dup2(fd[1], STDOUT_FILENO);
		exec_bin(data, info);
		// exit (data->exit_proc_number);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void pipework(t_data *data, t_info *info)
{
	// int i;
	t_info *tmp;

	tmp = info;
	// int	filein;
	// int	fileout;
	while (tmp && tmp->pipe == 1)
	{
		child_process(data, tmp);
		tmp = tmp->next;
	}
	dup2(1, STDOUT_FILENO);
	exec_bin(data, tmp);

}