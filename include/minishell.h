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

typedef struct s_data
{
    char **envp;
    
    char *str;
   // char **arg_per_one;
    char **history;
    //int breakpoint;
    char status;
    //char cntrl;
    //char *str_for_semocolon;
    t_list *first_elem;
    
}              t_data;

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


//typedef struct s_token{
//	char			*word;
//	char			value;
//	struct s_token	*next;
//	struct s_token	*prev;
//}				t_token;

#endif
