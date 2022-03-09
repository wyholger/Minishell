/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:54:51 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/09 21:31:23 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_arg(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	check_str_is_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit((int)str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	signal_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	ft_lstclear(&data->env);
	info_clear(&data->info);
	free(data->pid);
	if (data->pwd_old != NULL)
		free(data->pwd_old);
	free(data->pwd_now);
	free(data->pwd_home);
	free(data->pwd_start);
	exit(data->exit_proc_number);
}

void	exit_my(t_data *data, t_info *tmp)
{
	if (tmp->arg[1] != NULL && check_str_is_int(tmp->arg[1]) == 1)
		data->exit_proc_number = ft_atoi(tmp->arg[1]);
	if (count_arg(tmp->arg) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_proc_number = 130;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	ft_lstclear(&data->env);
	info_clear(&data->info);
	free(data->pid);
	if (data->pwd_old != NULL)
		free(data->pwd_old);
	free(data->pwd_now);
	free(data->pwd_home);
	free(data->pwd_start);
	exit(data->exit_proc_number);
}
