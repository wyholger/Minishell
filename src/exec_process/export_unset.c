/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:12:33 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/25 15:27:40 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_logic(t_data *data, t_info *tmp, int flag, int i)
{
	char	**for_split;
	t_list	*tmp_env;

	for_split = ft_split(tmp->arg[i], '=');
	tmp_env = search_token_in_envp(data, for_split[0]);
	if (tmp_env == NULL)
	{
		ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(tmp->arg[i])));
	}
	else
	{
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(tmp->arg[i])));
	}
	split_free(for_split);
	if (flag != 1)
		exit_exec(data, 0);
}

void	export_error_msg(t_data *data, char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	exit_exec(data, 1);
}

void	export(t_data *data, t_info *tmp)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (tmp->arg[1] != NULL)
	{
		while (tmp->arg[i])
		{
			if (ft_isalpha(tmp->arg[i][0]) == 1 || tmp->arg[i][0] == '_')
				export_logic(data, tmp, flag, i);
			else
			{
				export_error_msg(data, tmp->arg[i]);
				flag = 1;
			}
			i++;
		}
	}
	else
	{
		export_if_no_arg(data);
		exit_exec(data, 0);
	}
}

void	unset(t_data *data, t_info *tmp)
{
	char	**for_split;
	t_list	*tmp_env;

	if (tmp->arg[1] != NULL)
	{
		if (ft_isalpha(tmp->arg[1][0]) == 1 || tmp->arg[1][0] == '_')
		{
			for_split = ft_split(tmp->arg[1], '=');
			tmp_env = search_token_in_envp(data, for_split[0]);
			if (tmp_env != NULL)
				ft_lstdelone(&tmp_env);
			split_free(for_split);
			exit_exec(data, 0);
		}
		else
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(tmp->arg[1], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			exit_exec(data, 1);
		}
	}
}
