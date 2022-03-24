/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:56:03 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/24 19:29:21 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	serch_bin(t_data *data, t_info *info, char **env)
{
	char	*path;

	path = init_path_for_execve(data, info);
	if (path != NULL)
		data->exit_proc_number = execve(path, info->arg, env);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->command, 2);
		ft_putstr_fd(": command not found\n", 2);
		split_free(env);
		exit (127);
	}
}

void	exec_bin(t_data *data, t_info *info)
{
	char	**env;

	env = env_list_to_map(data);
	serch_bin(data, info, env);
	exit (data->exit_proc_number);
}

void	init_pid(t_data *data)
{
	int	i;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * (info_size(data->info) + 1));
	if (!data->pid)
		exit (0);
	while (i <= info_size(data->info))
	{
		data->pid[i] = -1;
		i++;
	}
}

void	wait_pid(t_data *data)
{
	int	i;

	i = 0;
	while (data->pid[i] != -1)
	{
		if (waitpid(data->pid[i], &data->exit_proc_number, 0) == -1)
		{
			return (perror("WAIT_PID"));
		}
		if (WIFSIGNALED(data->exit_proc_number))
		{
			data->exit_proc_number = 130;
		}
		else
		{
			data->exit_proc_number = WEXITSTATUS(data->exit_proc_number);
		}
		i++;
	}
}

void	add_pid(t_data *data, pid_t pid)
{
	int	i;

	i = 0;
	while (data->pid[i] != -1)
	{
		i++;
	}
	if (pid != 0)
		data->pid[i] = pid;
}
