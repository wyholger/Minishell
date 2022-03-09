/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:46:53 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 19:48:04 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_exec(t_data *data, int status)
{
	data->exit_proc_number = status;
}

char	**env_list_to_map(t_data *data)
{
	t_list	*tmp_env;
	char	**envp;
	int		len;
	int		i;

	i = 0;
	tmp_env = data->env;
	len = ft_lstsize(data->env);
	envp = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		envp[i] = ft_strdup(tmp_env->word);
		i++;
		tmp_env = tmp_env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	check_on_bild_cmd(t_info *tmp)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		return (1);
	if (ft_strcmp("cd", tmp->command) == 0)
		return (1);
	if (ft_strcmp("pwd", tmp->command) == 0)
		return (1);
	if (ft_strcmp("export", tmp->command) == 0)
		return (1);
	if (ft_strcmp("unset", tmp->command) == 0)
		return (1);
	if (ft_strcmp("env", tmp->command) == 0)
		return (1);
	if (ft_strcmp("exit", tmp->command) == 0)
		return (1);
	if (ft_strcmp("./minishell", tmp->command) == 0 || \
	ft_search_word_in_str_on_end(tmp->command, "/minishell") == 0)
		return (1);
	return (0);
}

void	delite_heredoke(t_info	*iter, t_data *data)
{
	char	*pwd_heredoke;
	char	*tmp;

	while (iter)
	{
		if (iter->name_her != NULL)
		{
			tmp = ft_strjoin("/", iter->name_her);
			pwd_heredoke = ft_strjoin(data->pwd_start, tmp);
			free(tmp);
			unlink(pwd_heredoke);
			free(pwd_heredoke);
		}
		iter = iter->next;
	}
}
