/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:20:01 by wyholger          #+#    #+#             */
/*   Updated: 2022/04/01 18:53:09 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_check_overflow(int flag_singl, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (flag_singl == 1)
		i = 1;
	if (str[i] != '9')
		return (1);
	tmp = malloc(10);
	ft_strlcpy(tmp, &str[i + 1], 10);
	flag_singl = ft_atoi(tmp);
	if (flag_singl > 223372036)
	{
		free(tmp);
		return (0);
	}
	ft_strlcpy(tmp, &str[i + 10], 10);
	flag_singl = ft_atoi(tmp);
	if (flag_singl > 854775807)
	{
		free(tmp);
		return (0);
	}
	return (1);
}
