/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:57:28 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/24 18:43:20 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_pipe_size(t_info *tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp->pipe == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
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
