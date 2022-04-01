/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:33:43 by wpitts            #+#    #+#             */
/*   Updated: 2022/04/01 18:42:54 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cntrl_c1(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	g_exit = 130;
}

void	ft_cntrl_slash(int sig)
{
	(void) sig;
	ft_putstr_fd("Quit: 3\n", 1);
	g_exit = 131;
}

void	ft_exec_sig(void)
{
	signal(SIGINT, &ft_cntrl_c1);
	signal(SIGQUIT, &ft_cntrl_slash);
}

void	ft_cntrl_c(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_exit = 1;
}

void	ft_sig_read(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &ft_cntrl_c);
	signal(SIGQUIT, SIG_IGN);
}
