/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:32:02 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 15:33:30 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parser(t_data *data)
{
	int	check;

	check = 0;
	check = ft_check_all_string(data);
	if (check == 0)
	{
		ft_pars_token(data, ft_skip_space(data));
		ft_treatmen_token(data);
		ft_filling_info(data, 0, 0);
	}
	else
		printf("Syntax Error\n");
	ft_lstclear(&data->token);
}
