/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:01:26 by wyholger          #+#    #+#             */
/*   Updated: 2022/03/23 16:32:44 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_redir_for_out_redir(t_data *data, t_info *info)
{
	int	filein;

	if (info->red != NULL && (ft_strcmp(info->red[0], "1") == 0 \
	|| ft_strcmp(info->red[0], "3") == 0))
	{
		filein = init_redirect_file_for_out(data, info, 1);
		dup2(filein, STDOUT_FILENO);
		close(filein);
		close(data->pipe_last[0]);
		close(data->pipe_last[1]);
		return (0);
	}
	return (1);
}
