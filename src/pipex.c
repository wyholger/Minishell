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
		if (check_on_bild_cmd(info) == 1)
		{
			exec_build_cmd(data, info, 1);
			exit(data->exit_proc_number);
		}
		else
			exec_bin(data, info);
		// exit (data->exit_proc_number);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		// waitpid(pid, NULL, 0);
	}
}

int	open_file(t_data *data, char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		data->exit_proc_number = 1;
		printf("ERROR\n");
		exit(1);
	}
	return (file);
}

int	init_redirect_file(t_data *data, t_info *info)
{
	int i;
	int	filein;

	i = 0;
	if (ft_strcmp(info->red[0], "2") == 0)
		i += 2;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "1") == 0)
			filein = open_file(data, info->red[i+1], 1);
		if (ft_strcmp(info->red[i], "3") == 0)
			filein = open_file(data, info->red[i+1], 0);
		i+=2;
	}
	return (filein);
}

t_info	*pipework(t_data *data, t_info *info)
{
	// int i;
	t_info	*tmp;
	int		filein;
	int		fileout;
	int     pid;

	tmp = info;
	filein = 1;
	if (tmp->red != NULL && ft_strcmp(tmp->red[0], "2") == 0)
	{
		fileout = open_file(data, tmp->red[1], 1);
		dup2(fileout, STDIN_FILENO);
	}
	while (tmp && tmp->pipe == 1)
	{
		// printf("22222_PPPPPPPPPPPPPPPPP\n");
		child_process(data, tmp);
		tmp = tmp->next;
	}
	if (tmp->red != NULL)
	{
		filein = init_redirect_file(data, tmp);
		dup2(filein, STDOUT_FILENO);
		// ft_putstr_fd("AAAAAA\n", filein);
	}
	else
		dup2(1, STDOUT_FILENO);
		
	if (check_on_bild_cmd(tmp) == 1)
	{
		exec_build_cmd(data, info, filein);
		// dup2(1, STDOUT_FILENO);
		// close(filein);
		// close(1);
		// exit(data->exit_proc_number);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			exec_bin(data, tmp);
	}
	// printf("33333_PPPPPPPPPPPPPPPPP\n");
	dup2(data->std_out, STDOUT_FILENO);
	return (tmp);
	// close(filein);
}