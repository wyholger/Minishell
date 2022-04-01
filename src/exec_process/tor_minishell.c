/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tor_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:48:42 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/25 16:02:00 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increment_shell_in_env(t_data *data)
{
	t_list	*tmp_env;
	int		lvl;
	char	**for_split;

	tmp_env = search_token_in_envp(data, "SHLVL");
	if (tmp_env != NULL)
	{
		for_split = ft_split(tmp_env->word, '=');
		lvl = ft_atoi(for_split[1]);
		lvl++;
		if (lvl > 1000)
		{
			ft_putstr_fd("minishell: warning: shell level ", 2);
			ft_putstr_fd("(1001) too high, resetting to 1\n", 2);
			lvl = 1;
		}
		split_free(for_split);
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("SHLVL=", \
		ft_itoa(lvl))));
	}
}

void	decrement_shell_in_env(t_data *data)
{
	t_list	*tmp_env;
	int		lvl;
	char	**for_split;

	tmp_env = search_token_in_envp(data, "SHLVL");
	if (tmp_env != NULL)
	{
		for_split = ft_split(tmp_env->word, '=');
		lvl = ft_atoi(for_split[1]);
		if (lvl > 1)
			lvl--;
		split_free(for_split);
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("SHLVL=", \
		ft_itoa(lvl))));
	}
}

void	tor_minishell(t_data *data, t_info *tmp)
{
	char	**env;
	pid_t	pid;

	env = NULL;
	increment_shell_in_env(data);
	env = env_list_to_map(data);
	decrement_shell_in_env(data);
	pid = fork();
	add_pid(data, pid);
	if (pid == 0)
		serch_bin(data, tmp, env);
	split_free(env);
}
