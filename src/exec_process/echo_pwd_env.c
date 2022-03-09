/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:04 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 19:58:15 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(t_data *data, t_info *tmp)
{
	int	i;

	i = 1;
	if (tmp->arg != NULL && ft_strcmp(tmp->arg[1], "$?") == 0)
	{
		ft_putnbr_fd(data->exit_proc_number, 1);
		if (tmp->flag == 0)
			ft_putstr_fd("\n", 1);
	}
	else if (tmp->arg != NULL)
	{
		while (tmp->arg[i])
		{
			ft_putstr_fd(tmp->arg[i], 1);
			i++;
			if (tmp->arg[i])
				ft_putstr_fd(" ", 1);
		}
		if (tmp->flag == 0)
			ft_putstr_fd("\n", 1);
	}
	exit_exec(data, 0);
}

void	pwd(t_data *data, t_info *tmp)
{
	char	*str;

	str = NULL;
	(void)data;
	(void)tmp;
	str = data->pwd_now;
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	exit_exec(data, 0);
}

void	env(t_data *data)
{
	t_list	*tmp_env;

	tmp_env = data->env;
	while (tmp_env != NULL)
	{
		ft_putstr_fd(tmp_env->word, 1);
		ft_putchar_fd('\n', 1);
		tmp_env = tmp_env->next;
	}
	exit_exec(data, 0);
}
