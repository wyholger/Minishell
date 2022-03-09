/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:55:53 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 19:47:42 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_for_pipe(t_data *data, t_info *info)
{
	if (check_on_bild_cmd(info) == 1)
	{
		exec_build_cmd(data, info);
		exit(data->exit_proc_number);
	}
	else
	{
		exec_bin(data, info);
	}
}

void	start_pipe(t_data *data, t_info *info)
{
	pid_t	pid;
	int		filein;

	pipe(data->pipe_last);
	pid = fork();
	add_pid(data, pid);
	if (pid == 0)
	{
		if (info->red != NULL && ft_strcmp(info->red[0], "2") == 0)
		{
			filein = init_redirect_file_for_in(data, info, 1);
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
		close(data->pipe_last[0]);
		dup2(data->pipe_last[1], STDOUT_FILENO);
		close(data->pipe_last[1]);
		exec_for_pipe(data, info);
	}
	else
		close(data->pipe_last[1]);
}

void	mid_pipe(t_data *data, t_info *info)
{
	int		pipe_new[2];
	pid_t	pid;

	pipe(pipe_new);
	pid = fork();
	add_pid(data, pid);
	if (pid == 0)
	{
		dup2(data->pipe_last[0], STDIN_FILENO);
		close(data->pipe_last[0]);
		dup2(pipe_new[1], STDOUT_FILENO);
		close(pipe_new[1]);
		exec_for_pipe(data, info);
	}
	else
	{
		close(data->pipe_last[0]);
		data->pipe_last[0] = pipe_new[0];
		data->pipe_last[1] = pipe_new[1];
		close(data->pipe_last[1]);
	}
}

void	end_pipe(t_data *data, t_info *info)
{
	pid_t	pid;
	int		fileout;

	pid = fork();
	add_pid(data, pid);
	if (pid == 0)
	{
		if (info->red != NULL)
		{
			fileout = init_redirect_file_for_out(data, info, 1);
			if (fileout != -1)
			{
				dup2(fileout, STDOUT_FILENO);
				close(fileout);
			}
		}
		dup2(data->pipe_last[0], STDIN_FILENO);
		close(data->pipe_last[0]);
		exec_for_pipe(data, info);
	}
	close(data->pipe_last[0]);
}

t_info	*exec_pipe_redirect(t_data *data, t_info *info)
{
	int		i;

	i = 1;
	start_pipe(data, info);
	info = info->next;
	while (i < data->pipe_size)
	{
		mid_pipe(data, info);
		info = info->next;
		i++;
	}
	end_pipe(data, info);
	return (info);
}
