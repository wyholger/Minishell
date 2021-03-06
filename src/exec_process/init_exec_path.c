/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:52 by wyholger          #+#    #+#             */
/*   Updated: 2022/04/01 18:49:37 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*absolute_path(t_data *data, t_info *info)
{
	char	*path;

	path = NULL;
	path = info->command;
	if (access(path, 0) == 0)
		data->flag_old_pwd = 1;
	return (path);
}

char	*real_way(t_data *data, t_info *info)
{
	char	*tmp_path;
	char	*path;

	tmp_path = ft_strtrim_start(info->command, ".");
	path = ft_strjoin(data->pwd_now, tmp_path);
	free(tmp_path);
	if (access(path, 0) == 0)
		data->flag_old_pwd = 1;
	else
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	check_path(char *path, t_data *data)
{
	if (access(path, 0) == 0)
	{
		data->flag_old_pwd = 1;
		return (1);
	}
	return (0);
}

char	*path_by_path(t_data *data, t_info *info)
{
	int		i;
	char	**split;
	char	*path;
	char	*tmp_path;

	i = 0;
	tmp_path = ft_strjoin("/", info->command);
	split = NULL;
	split = ft_split(search_in_envp(data, "PATH"), ':');
	if (split == NULL)
		return (NULL);
	while (split[i])
	{
		path = ft_strjoin(split[i], tmp_path);
		if (check_path(path, data))
			break ;
		i++;
		free(path);
		path = NULL;
	}
	free(tmp_path);
	split_free(split);
	return (path);
}

char	*init_path_for_execve(t_data *data, t_info *info)
{
	char	*path;

	path = NULL;
	data->flag_old_pwd = 0;
	if (info->command[0] == '/')
		path = absolute_path(data, info);
	else if (info->command[0] == '.' && info->command[1] == '/')
		path = real_way(data, info);
	else
		path = path_by_path(data, info);
	if (data->flag_old_pwd == 0)
		return (NULL);
	return (path);
}
