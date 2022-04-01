/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:54:51 by wyholger          #+#    #+#             */
/*   Updated: 2022/04/01 18:54:38 by wyholger         ###   ########.fr       */
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
	int	flag_singl;

	i = 0;
	flag_singl = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
		{
			flag_singl = 1;
			i++;
			continue ;
		}
		if (ft_isdigit((int)str[i]) == 0)
			return (0);
		i++;
	}
	if ((flag_singl == 1 && i == 1) || (i > 19 && flag_singl == 0) \
	|| (flag_singl == 1 && i > 20))
		return (0);
	if (i < 19)
		return (1);
	if (i == 19)
		return (exit_check_overflow(flag_singl, str));
	return (1);
}

void	signal_exit(t_data *data)
{
	rl_clear_history();
	ft_putstr_fd("\033[1Aminishell$ exit\n", 1);
	ft_lstclear(&data->env);
	info_clear(&data->info);
	if (data->pwd_old != NULL)
		free(data->pwd_old);
	free(data->pwd_now);
	free(data->pwd_home);
	free(data->pwd_start);
	exit(data->exit_proc_number);
}

void	exit_error(t_data *data, t_info *tmp)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(tmp->arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->exit_proc_number = 255;
}

void	exit_my(t_data *data, t_info *tmp)
{
	if (tmp->arg[1] != NULL && check_str_is_int(tmp->arg[1]) == 1)
		data->exit_proc_number = ft_atoi(tmp->arg[1]);
	ft_putstr_fd("exit\n", 1);
	if (tmp->arg[1] != NULL && check_str_is_int(tmp->arg[1]) == 0)
		exit_error(data, tmp);
	else if (count_arg(tmp->arg) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_proc_number = 1;
		return ;
	}
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
