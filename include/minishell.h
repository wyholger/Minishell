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
# include "../libft/libft.h"

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
    char	*str;
    int		exit_proc_number;
    t_list	*token;
    t_info	*info;
	pid_t	*pid;
    int		breakpoint;
	int		status;
    
}              t_data;



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
#endif
