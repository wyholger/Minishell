/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyholger <wyholger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:04:44 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/25 15:27:27 by wyholger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <errno.h>
# include <termios.h>

# define MINISHELL_MSG "minishell$ "

int	g_exit;

typedef struct s_info
{
	char			*command;
	int				count_command;
	char			**arg;
	int				flag;
	char			**red;
	t_list			*redir;
	char			*name_her;
	int				pipe;
	int				semocolon;
	struct s_info	*next;
	struct s_info	*prev;
}				t_info;

typedef struct s_data
{
	char	**envp;
	t_list	*env;
	char	*str;
	int		exit_proc_number;
	t_list	*token;
	t_info	*info;
	pid_t	*pid;
	int		breakpoint;
	int		status;
	int		std_in;
	int		std_out;
	int		pipe_size;
	int		pipe_last[2];
	int		filein;
	int		fileout;
	int		flag_old_pwd;
	char	*pwd_start;
	char	*pwd_now;
	char	*pwd_home;
	char	*pwd_old;
}				t_data;

void	ft_parser(t_data *data);
void	split_free(char **str);
char	*search_in_envp(t_data *data, char *str);
/*
Функуии для работы с листами инфо
*/
t_info	*info_new(void);
void	info_add_back(t_info **lst, t_info *new);
int		info_clear(t_info **lst);
int		info_print_content(t_info **lst);
int		info_size(t_info *lst);
t_info	*pipework(t_data *data, t_info *info);
void	child_process(t_data *data, t_info *info);
void	exec_bin(t_data *data, t_info *info);
int		init_redirect_file(t_data *data, t_info *info);
int		open_file(t_data *data, char *argv, int i, int flag_fork);
void	exec_build_cmd(t_data *data, t_info *tmp);
int		check_on_bild_cmd(t_info *tmp);
int		search_num_line_in_envp(t_data *data, char *str);
t_list	*search_token_in_envp(t_data *data, char *str);
void	add_pid(t_data *data, pid_t pid);
t_info	*exec_pipe_redirect(t_data *data, t_info *info);
int		init_redirect_file_for_in(t_data *data, t_info *info, int flag_fork);
int		init_redirect_file_for_out(t_data *data, t_info *info, int flag_fork);
char	*init_path_for_execve(t_data *data, t_info *info);
void	serch_bin(t_data *data, t_info *info, char **env);
void	swap_token(t_list	*swap_token);
void	print_env_for_export(t_list *lst);
void	export_if_no_arg(t_data *data);
void	exit_exec(t_data *data, int status);
void	export(t_data *data, t_info *tmp);
void	export_logic(t_data *data, t_info *tmp, int flag, int i);
void	export_error_msg(t_data *data, char *arg);
void	cd(t_data *data, t_info *tmp);
void	unset(t_data *data, t_info *tmp);
void	decrement_shell_in_env(t_data *data);
void	increment_shell_in_env(t_data *data);
void	tor_minishell(t_data *data, t_info *tmp);
char	**env_list_to_map(t_data *data);
void	env(t_data *data);
void	pwd(t_data *data, t_info *tmp);
void	echo(t_data *data, t_info *tmp);
void	exit_my(t_data *data, t_info *tmp);
int		check_str_is_int(char *str);
int		count_arg(char **str);
void	exec_cmd_one(t_data *data, t_info *info);
void	init_redirect(t_data *data, t_info *info, int flag_fork, int flag_in);
int		init_redirect_file_for_out(t_data *data, t_info *info, int flag_fork);
int		init_redirect_file_for_in(t_data *data, t_info *info, int flag_fork);
int		init_pipe_size(t_info *tmp);
char	*init_path_for_execve(t_data *data, t_info *info);
char	*path_by_path(t_data *data, t_info *info);
char	*real_way(t_data *data, t_info *info);
char	*absolute_path(t_data *data, t_info *info);
void	wait_pid(t_data *data);
void	init_pid(t_data *data);
void	ft_init_struct(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);
void	split_str(t_data *data);
void	delite_heredoke(t_info	*iter, t_data *data);
void	signal_exit(t_data *data);
void	ft_sig_read(void);
int		pipe_redir_for_out_redir(t_data *data, t_info *info);

//parser

void	ft_pars_token(t_data *data, int i);
void	ft_treatmen_token(t_data *data);
int		ft_check_all_string(t_data *data);
void	ft_filling_info(t_data *data, int p);
int		ft_tok_dollar(t_list *token, int i, t_data *data);
int		ft_tilda(t_list *token, t_data *data, int i, int k);
void	ft_token_red_treat(t_list *token);
void	ft_quotes(t_data *data, int *i);
void	ft_double_quotes(t_data *data, int *i);
int		ft_skip_space(t_data *data);
void	ft_help_quo(t_data *data, int *i);
int		ft_len_for_pipe2(t_list *token, int i);
int		ft_len_for_pipe(t_list *token, int i);
void	ft_filling_red(t_info *info, char *des);
char	*generate_heredoke_name(int p);
void	init_heredok(t_info *des);
int		ft_check_redmal(t_list *token, int i);
void	ft_fill_comm(t_info *des, int p, t_data *data);
void	ft_des_mal(t_info *des, int p, t_data *data);
int		ft_fil_fl(t_info *des, t_data *data, int p, int k);
void	ft_red_fil(t_list *tmp, t_list *tmp1, t_info *des, int *k);
int		ft_alpha_help(t_list *token);
int		ft_dollar_digit(t_list *token, t_data *data, int i);
void	ft_skip_to_dol(t_list *token, int *i);
char	*ft_fil_dol_ex(t_list *token, char *tmp, char *str, int i);
int		ft_dollar_exit(t_list *token, t_data *data);
void	ft_help_key(char *tmp, char *str, int *h);
char	*ft_mal_tmp(t_list *token, char *str);

#endif
