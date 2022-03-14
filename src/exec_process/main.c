/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:34:15 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/14 17:47:15 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec(t_data *data)
{
	t_info	*tmp;
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

void	main_process(t_data *data)
{
	add_history(data->str);
	ft_parser(data);
	init_pid(data);
	exec(data);
	wait_pid(data);
	delite_heredoke(data->info, data);
	info_clear(&data->info);
	data->info = NULL;
	free(data->str);
    free(data->pid);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_init_struct(&data, envp);
	while (data.status != 0)
	{
		ft_sig_read();
		data.str = 0;
		data.str = readline(MINISHELL_MSG);
		if (data.str == 0)
            signal_exit(&data);
		if (data.str != 0)
			main_process(&data);
	}
	rl_clear_history();
	return (0);
}
