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

# define MINISHELL_MSG "\033[35mminishell$ \033[0m"

typedef struct s_info
{
	char *command;
	int count_command;
	char **arg;
	// -n for echo
	int flag;
	// >(1)
	char **red;
	// <(2)
	// >>(3)
	// <<(4)
	// 2>(5)
	// 2>>(6)
	int pipe;
	int semocolon;
	struct s_info *next;
	struct s_info *prev;
}              t_info;

typedef struct s_data
{
	char	**envp;
    t_list  *env;
	char	*str;
	int		exit_proc_number;
	t_list	*token;
	t_info	*info;
	pid_t	*pid;
	int		breakpoint;
	int		status;
	int		std_in;
	int		std_out;
    int     pipe_size;
	int		pipe_last[2];
	int 	filein;
	int 	fileout;
    char    *pwd_start;
    char    *pwd_now;
    char    *pwd_home;
    char    *pwd_old;

}              t_data;


void ft_parser(t_data *data);
void	split_free(char **str);
char	*search_in_envp(t_data *data, char *str);
/*
Функуии для работы с листами инфо
*/
t_info	*info_new();
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
#endif
