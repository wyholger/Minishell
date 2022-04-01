/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:58:29 by wyholger          #+#    #+#             */
/*   Updated: 2022/04/01 18:43:24 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file(t_data *data, char *argv, int i, int flag_fork)
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
		ft_putstr_fd("minishell: ", 2);
		perror(argv);
		errno = 0;
		if (flag_fork == 1)
			exit(1);
	}
	return (file);
}

int	check_on_open_in_file(int fileout, int pre_fileout)
{
	if (fileout != -1)
	{
		close(fileout);
		fileout = pre_fileout;
	}
	return (fileout);
}

int	init_redirect_file_for_in(t_data *data, t_info *info, int flag_fork)
{
	int	i;
	int	filein;

	filein = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "2") == 0)
		{
			filein = open_file(data, info->red[i + 1], 2, flag_fork);
		}
		else
			break ;
		i += 2;
	}
	return (filein);
}

int	init_redirect_file_for_out(t_data *data, t_info *info, int flag_fork)
{
	int	i;
	int	fileout;
	int	pre_fileout;

	fileout = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "1") == 0)
			fileout = open_file(data, info->red[i + 1], 1, flag_fork);
		if (ft_strcmp(info->red[i], "3") == 0)
			fileout = open_file(data, info->red[i + 1], 0, flag_fork);
		if (ft_strcmp(info->red[i], "2") == 0)
		{
			pre_fileout = open_file(data, info->red[i + 1], 2, flag_fork);
			if (pre_fileout != -1)
				close(pre_fileout);
		}
		if (fileout != -1 && info->red[i + 2] != NULL && \
		((ft_strcmp(info->red[i + 2], "1") == 0) || \
		(ft_strcmp(info->red[i + 2], "3") == 0)))
			close(fileout);
		i += 2;
	}
	return (fileout);
}

void	init_redirect(t_data *data, t_info *info, int flag_fork, int flag_in)
{
	int	filein;
	int	fileout;

	if ((info->red != NULL && ft_strcmp(info->red[0], "2") == 0) && \
	flag_in == 1)
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
