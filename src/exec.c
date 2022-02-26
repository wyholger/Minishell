#include "../include/minishell.h"

int init_pipe_size(t_info *tmp)
{
	int i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp->pipe == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	init_redirect_file_for_in(t_data *data, t_info *info, int flag_fork)
{
	int i;
	int	filein;

	filein = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "2") == 0)
			filein = open_file(data, info->red[i+1], 2, flag_fork);
		else
			break ;
		i+=2;
	}
	return (filein);
}

int	init_redirect_file_for_out(t_data *data, t_info *info, int flag_fork)
{
	int i;
	int fileout;

	fileout = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "1") == 0)
			fileout = open_file(data, info->red[i+1], 1, flag_fork);
		if (ft_strcmp(info->red[i], "3") == 0)
			fileout = open_file(data, info->red[i+1], 0, flag_fork);
		if (fileout != -1 && info->red[i+2] != NULL && ((ft_strcmp(info->red[i+2], "1") == 0) || (ft_strcmp(info->red[i+2], "3") == 0)))
			close(fileout);
		i+=2;
	}
	return (fileout);
}

void	init_redirect(t_data *data, t_info *info, int flag_fork, int flag_in)
{
	int	filein;
	int fileout;

	if ((info->red != NULL && ft_strcmp(info->red[0], "2") == 0) && flag_in == 1)
	{
		filein = init_redirect_file_for_in(data, info, flag_fork);
		if (filein != -1)
		{
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
	}
	if (info->red != NULL)
	{
		fileout = init_redirect_file_for_out(data, info, flag_fork);
		if (fileout != -1)
		{
			dup2(fileout, STDOUT_FILENO);
			close(fileout);
		}
	}
}

void	exec_cmd_one(t_data *data, t_info *info)
{
	pid_t	pid;

	if (check_on_bild_cmd(info) == 1)
	{
		init_redirect(data, info, 0, 0);
		exec_build_cmd(data, info);
		dup2(data->std_out, STDOUT_FILENO);
	}
	else
	{
		pid = fork();
		add_pid(data, pid);
		if (pid == 0)
		{
			init_redirect(data, info, 1, 1);
			exec_bin(data, info);
		}
	}
}
