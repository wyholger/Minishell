/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:55:45 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 19:55:46 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_build_cmd(t_data *data, t_info *tmp)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		echo(data, tmp);
	if (ft_strcmp("cd", tmp->command) == 0)
		cd(data, tmp);
	if (ft_strcmp("pwd", tmp->command) == 0)
		pwd(data, tmp);
	if (ft_strcmp("export", tmp->command) == 0)
		export(data, tmp);
	if (ft_strcmp("unset", tmp->command) == 0)
		unset(data, tmp);
	if (ft_strcmp("env", tmp->command) == 0)
		env(data);
	if (ft_strcmp("exit", tmp->command) == 0)
		exit_my(data, tmp);
	if (ft_search_word_in_str_on_end(tmp->command, "/minishell") == 0)
		tor_minishell(data, tmp);
}
