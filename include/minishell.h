#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# define MINISHELL_MSG "\033[35mminishell$ \033[0m"

typedef struct s_info
{
	char *command;
	int cont_command;
	char *arg;
	// -n for echo
	char *flag;
	// >
	char red_1;
	// <
	char red_2;
	// >>
	char red_3;
	// <<
	char red_4;
	
	char pipe;
	struct s_info *next;
	struct s_info *prev;
}              t_info;

typedef struct s_data
{
    char **envp;
    char *str;
    int exit_proc_number;
    t_list *first_elem;
    t_info *first_elem_info;
    int breakpoint;
	int status;
    
}              t_data;



void	split_free(char **str);
char	*search_in_envp(t_data *data, char *str);

#endif
