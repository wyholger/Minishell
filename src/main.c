#include "../include/minishell.h"

void split_str(t_data *data)
{
	char **for_split;
	int	i;
	
	i = 0;
	for_split = ft_split(data->str, ' ');
	while (for_split[i])
	{
		ft_lstadd_back(&data->token, ft_lstnew(for_split[i]));
		i++;
	}
	ft_lstprint_content(&data->token);
	ft_lstclear(&data->token);
	split_free(for_split);
}

void	init_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

void	ft_init_struct(t_data *data, char **envp)
{
	(void)envp;
	data->status = 1;
	data->token = NULL;
	data->info = NULL;
	data->env = NULL;
	init_envp(data, envp);
	data->exit_proc_number = 0;
	data->std_in = dup(STDOUT_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->pwd_start = search_in_envp(data, "PWD");
	data->pwd_now = search_in_envp(data, "PWD");
	data->pwd_old = search_in_envp(data, "PWD");
	data->pwd_home = search_in_envp(data, "HOME");
}

int	check_on_bild_cmd(t_info *tmp)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		return (1);
	if (ft_strcmp("cd", tmp->command) == 0)
		return (1);
	if (ft_strcmp("pwd", tmp->command) == 0)
		return (1);
	if (ft_strcmp("export", tmp->command) == 0)
		return (1);
	if (ft_strcmp("unset", tmp->command) == 0)
		return (1);
	if (ft_strcmp("env", tmp->command) == 0)
		return (1);	
	if (ft_strcmp("exit", tmp->command) == 0)
		return (1);
	return (0);
}

void	exit_exec(t_data *data, int status)
{
	data->exit_proc_number = status;
}

void	echo(t_data *data, t_info *tmp, int filein)
{
	int i;

	i = 1;
	(void)data;

	// printf("BBBBB\n");
	// printf("%s\n", tmp->arg[i]);
	// ft_putstr_fd(tmp->arg[i], filein);
	if (tmp->arg != NULL && ft_strcmp(tmp->arg[1], "$?") == 0)
	{
		ft_putnbr_fd(data->exit_proc_number, filein);
		if (tmp->flag == 0)
			ft_putstr_fd("\n", filein);
	}
	else if (tmp->arg != NULL)
	{
		while (tmp->arg[i])
		{
			ft_putstr_fd(tmp->arg[i], filein);
			i++;
			if (tmp->arg[i])
				ft_putstr_fd(" ", filein);
		}
		if (tmp->flag == 0)
			ft_putstr_fd("\n", filein);
	}
	exit_exec(data, 0);
}

void	pwd(t_data *data, t_info *tmp, int filein)
{
	char *str;

	str = NULL;
	(void)data;
	(void)tmp;
	str = data->pwd_now;
	ft_putstr_fd(str, filein);
	ft_putchar_fd('\n', filein);
}

void	env(t_data *data, t_info *tmp, int filein)
{
	t_list *tmp_env;
	// char *line;
	(void)tmp;
	tmp_env = data->env;
	// line = NULL;
	// if (tmp->arg[1] == NULL)
	// {
	while (tmp_env)
	{
		ft_putstr_fd(tmp_env->word, filein);
		ft_putchar_fd('\n', filein);
		tmp_env = tmp_env->next;
	}
	data->exit_proc_number = 0;
	// }
	// else
	// {
	// 	line = search_in_envp(data, tmp->arg[1]);
	// 	if (line != NULL)
	// 	{
	// 		ft_putstr_fd(line, filein);
	// 		ft_putstr_fd("\n", filein);
	// 		data->exit_proc_number = 0;
	// 	}
	// 	else
	// 	{
	// 		ft_putstr_fd("env: ", 2);
	// 		ft_putstr_fd(tmp->arg[1], 2);
	// 		ft_putstr_fd(": No such file or directory\n", 2);
	// 		data->exit_proc_number = 127;
	// 	}
		
	// }
}

void	cd(t_data *data, t_info *tmp, int filein)
{
	t_list	*tmp_env;
	int	i;

	i = 0;
	// printf("%s\n", tmp->arg[1]);
	if (tmp->arg[1] == NULL)
		tmp->arg[1] = ft_strdup(data->pwd_home);
	// chdir(tmp->arg[1]);
	(void)filein;
	if (chdir(tmp->arg[1]) == 0)
	{
		free(data->pwd_now);
		data->pwd_now = getcwd(NULL, 0);
		tmp_env = search_token_in_envp(data, "PWD");

		// line = search_num_line_in_envp(data, "PWD");
		if (tmp_env == NULL)
		{
			ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("PWD=", data->pwd_now)));
		}
		else
		{
			ft_lstdelone(&tmp_env);
			ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("PWD=", data->pwd_now)));
		}
		// if (tmp->arg[1][0] == '/' || tmp->arg[1][0] == '~')
		// {
		// 	free(data->pwd_now);
		// 	if (tmp->arg[1][0] == '~')
		// 		data->pwd_now = ft_strdup(data->pwd_home);
		// 	if (tmp->arg[1][0] == '/')
		// 		data->pwd_now = ft_strdup(tmp->arg[1]);
		// }
		// else
		// {
		// 	free(data->pwd_now);
		// 	if ()
		// }
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(tmp->arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	exec_build_cmd(t_data *data, t_info *tmp, int filein)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		echo(data, tmp, filein);
	if (ft_strcmp("cd", tmp->command) == 0)
		cd(data, tmp, filein);
	if (ft_strcmp("pwd", tmp->command) == 0)
		pwd(data, tmp, filein);
	// if (ft_strcmp("export", tmp->command) == 0)
	// 	return (1);
	// if (ft_strcmp("unset", tmp->command) == 0)
	// 	return (1);
	if (ft_strcmp("env", tmp->command) == 0)
		env(data, tmp, filein);
	// if (ft_strcmp("exit", tmp->command) == 0)
	// 	return (1);
	// return (0);
}

void	init_pid(t_data *data)
{
	int i;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * (info_size(data->info) + 1));
	if (!data->pid)
		exit (0); //add if 
	while (i <= info_size(data->info))
	{
		data->pid[i] = -1;
		i++;
	}
}

void	wait_pid(t_data *data)
{
	int i;

	i = 0;
	while (data->pid[i] != -1)
	{
//		printf("YYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n");
		if (waitpid(data->pid[i], &data->exit_proc_number, 0) == -1) {
			return (perror("WAIT_PID"));
		}
		if (WIFSIGNALED(data->exit_proc_number)) {
			data->exit_proc_number = 130;
		}
		else {
			data->exit_proc_number = WEXITSTATUS(data->exit_proc_number);
		}
		i++;
	}
}

void child_signal_handler(int sig)
{
	(void)sig;
}

void	add_pid(t_data *data, pid_t pid)
{
	int i;

	i = 0;
	while (data->pid[i] != -1)
	{
		i++;
	}
	data->pid[i] = pid;
}

// void	init_pipe_redir(t_data *data, t_info *info)
// {
// 	if (info->prev != NULL && info->prev->pipe == 1)
// 	{
	
// 	}
// }


void	serch_bin(t_data *data, t_info *info)
{
	int		i;
	int		flag;
	char	**split;
	char	*path;
	char	*command;

	i = 0;
	flag = 0;
	if (info->command[0] == '/')
	{
		path = info->command;
		if (access(path, 0) == 0)
		{
			data->exit_proc_number = execve(path, info->arg, data->envp);
			flag = 1;
		}
	}
	else 
	{
		command = ft_strjoin("/", info->command);
		split = NULL;
		split = ft_split(search_in_envp(data, "PATH"), ':');
		while (split[i])
		{
			path = ft_strjoin(split[i], command);
			if (access(path, 0) == 0)
			{
				printf("EXIT_NUM %d\n", data->exit_proc_number);
				data->exit_proc_number = execve(path, info->arg, data->envp);
				ft_putstr_fd("EXIT_NUM ", 1);
				ft_putnbr_fd(errno, 1);
				printf("EXIT_NUM %d\n", data->exit_proc_number);
				flag = 1;
				free(path);
				break ;
			}
			i++;
			free(path);
		}
		free(command);
		split_free(split);
	}
	if (flag == 0)
	{
		data->exit_proc_number = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	exec_bin(t_data *data, t_info *info)
{
	// int fd;

	// if (ft_strcmp(info->red[0], "1"))
	// {
	// 	fd = open(info->red[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (fd == -1)
	// 	{
	// 		data->exit_proc_number = E_FILE_OPEN;
			
	// 	}
	// }
	serch_bin(data, info);
	exit (data->exit_proc_number);
}

void	exec(t_data *data)
{
	t_info *tmp;
	pid_t	pid;

	tmp = data->info;
	printf("size info %d\n", info_size(tmp));




	// char *path = search_in_envp(data, "PWD");
	// chdir("src");

	// data->envp[search_num_line_in_envp(data, "PWD")] = "PWD=/Users/wyholger";
	
	
	
	
	while (tmp != NULL)
	{
		if (check_on_bild_cmd(tmp) == 1 && tmp->pipe == 0 && tmp->red == NULL)
			exec_build_cmd(data, tmp, 1);
		else if (tmp->pipe == 0 && tmp->red == NULL)
		{
			// printf("HHHHHHHHHH\n");
			pid = fork();
			if (pid == -1) {
				return ;
			}
			// else if (pid == 0) 
			// {
			// 	signal(SIGINT, child_signal_handler);
			// }
			add_pid(data, pid);
//			printf("PIDS %d, %d\n", data->pid[0], data->pid[1]);
//			printf("BLAH\n");
			if (pid == 0)
			{
				// printf("HHHHHHHHHH\n");
				// init_pipe_redir(data, tmp);
				exec_bin(data, tmp);
			}
		}
		else if (tmp->pipe == 1 || tmp->red != NULL)
		{
			tmp = pipework(data, tmp);
			// printf("jfksdjksafdhj\n");
			while (tmp && tmp->pipe == 1)
				tmp = tmp->next;
		}
		// printf("11111111111\n");
		tmp = tmp->next;
		// while (tmp && tmp->pipe == 1)
		// 	tmp = tmp->next;
	}
}

void    plug(t_data *data)
{
	t_info *tmp;

	info_add_back(&data->info, info_new());
	tmp = data->info;
	data->info->command = "env";
	data->info->count_command = 0;
	data->info->arg = ft_split("env PWD", ' ');
	data->info->flag = 0;
	data->info->red = NULL;
	data->info->semocolon = 1;
	data->info->pipe = 0;
	info_add_back(&data->info, info_new());
	tmp = tmp->next;
	tmp->command = "cd";
	tmp->count_command = 3;
	tmp->arg = ft_split("cd /../../..", ' ');;
	tmp->flag = 0;
	tmp->red = NULL;
	tmp->pipe = 0;
	tmp->semocolon = 1;
	info_add_back(&data->info, info_new());
	tmp = tmp->next;
	tmp->command = "env";
	tmp->count_command = 3;
	tmp->arg = ft_split("env PWD", ' ');
	tmp->flag = 0;
	tmp->red = NULL;
	tmp->pipe = 0;
	tmp->semocolon = 1;
	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "pwd";
	// tmp->count_command = 2;
	// tmp->arg = ft_split("pwd", ' ');
	// tmp->flag = 0;
	// tmp->red = NULL;
	// tmp->pipe = 0;
	// tmp->semocolon = 1;
	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "env";
	// tmp->count_command = 3;
	// tmp->arg = ft_split("env PWD", ' ');
	// tmp->flag = 0;
	// tmp->red = NULL;
	// tmp->pipe = 0;
	// tmp->semocolon = 1;
	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "ls";
	// tmp->count_command = 1;
	// tmp->arg = ft_split("ls", ' ');
	// tmp->flag = 0;
	// tmp->red = NULL;
	// tmp->pipe = 0;
	// tmp->semocolon = 1;

	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "ls";
	// tmp->count_command = 3;
	// tmp->arg = ft_split("ls", ' ');;
	// tmp->flag = 0;
	// tmp->red = ft_split("1 32", ' ');
	// tmp->pipe = 0;
	// tmp->semocolon = 0;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_data data;
	// char *str;
	
	ft_init_struct(&data, envp);
	// str = search_in_envp(&data, "PATH");
	// printf("%s\n", str);
	// free(str);
	plug(&data);
	// info_print_content(&data.info);
	// printf("jfksdjksafdhj\n");
	init_pid(&data);
	exec(&data);
	wait_pid(&data);
	
	// while (data.status != 0)
	// {
	// 	data.str = readline(MINISHELL_MSG);
	// 	split_str(&data);
	// 	//ft_parser
	// 	free(data.str);
	// }
	//free struct
}
