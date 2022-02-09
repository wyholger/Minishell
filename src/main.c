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
	data->pwd_old = search_in_envp(data, "OLDPWD");
	data->pwd_home = search_in_envp(data, "HOME");
	data->pipe_size = 0;
	data->filein = 0;
	data->fileout = 1;
	errno = 0;
}

void increment_shell_in_env(t_data *data)
{
	t_list *tmp_env;
	int		lvl;
	char	**for_split;

	tmp_env = search_token_in_envp(data, "SHLVL");
	if (tmp_env != NULL)
	{
		for_split = ft_split(tmp_env->word, '=');
		lvl = ft_atoi(for_split[1]);
		lvl++;
		split_free(for_split);
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(lvl))));
	}
}

void decrement_shell_in_env(t_data *data)
{
	t_list	*tmp_env;
	int		lvl;
	char	**for_split;

	tmp_env = search_token_in_envp(data, "SHLVL");
	if (tmp_env != NULL)
	{
		for_split = ft_split(tmp_env->word, '=');
		lvl = ft_atoi(for_split[1]);
		if (lvl > 1)
			lvl--;
		split_free(for_split);
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(lvl))));
	}
}

char **env_list_to_map(t_data *data)
{
	t_list *tmp_env;
	char **envp;
	int len;
	int i;

	i = 0;
	tmp_env = data->env;
	len = ft_lstsize(data->env);
	envp = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		envp[i] = ft_strdup(tmp_env->word);
		i++;
		tmp_env = tmp_env->next;
	}
	envp[i] = NULL;
	return (envp);
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
	if (ft_strcmp("./minishell", tmp->command) == 0 || ft_search_word_in_str_on_end(tmp->command, "/minishell") == 0)
		return (1);
	return (0);
}

void	exit_exec(t_data *data, int status)
{
	data->exit_proc_number = status;
}

void	echo(t_data *data, t_info *tmp)
{
	int i;

	i = 1;
	(void)data;
	if (tmp->arg != NULL && ft_strcmp(tmp->arg[1], "$?") == 0)
	{
		ft_putnbr_fd(data->exit_proc_number, 1);
		if (tmp->flag == 0)
			ft_putstr_fd("\n", 1);
	}
	else if (tmp->arg != NULL)
	{
		while (tmp->arg[i])
		{
			ft_putstr_fd(tmp->arg[i], 1);
			i++;
			if (tmp->arg[i])
				ft_putstr_fd(" ", 1);
		}
		if (tmp->flag == 0)
			ft_putstr_fd("\n", 1);
	}
	exit_exec(data, 0);
}

void	pwd(t_data *data, t_info *tmp)
{
	char *str;

	str = NULL;
	(void)data;
	(void)tmp;
	str = data->pwd_now;
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	exit_exec(data, 0);
}

void	env(t_data *data, t_info *tmp)
{
	t_list *tmp_env;

	(void)tmp;
	tmp_env = data->env;
	while (tmp_env != NULL)
	{
		ft_putstr_fd(tmp_env->word, 1);
		ft_putchar_fd('\n', 1);
		tmp_env = tmp_env->next;
	}
	exit_exec(data, 0);
}

void	cd(t_data *data, t_info *tmp)
{
	t_list	*tmp_env;
	int		flag_old_pwd;
	char	*path;

	flag_old_pwd = 0;
	path = ft_strdup(tmp->arg[1]);
	if (path == NULL)
		path = ft_strdup(data->pwd_home);
	if (ft_strcmp (path, "-") == 0)
	{
		if (data->pwd_old == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			exit_exec(data, 1);
			return ;
		}
		else
		{
			free(path);
			path = NULL;
			path = ft_strdup(data->pwd_old);
			flag_old_pwd = 1;
		}
	}
	if (chdir(path) == 0)
	{
		if (flag_old_pwd == 1)
		{
			ft_putstr_fd (data->pwd_old, 1);
			ft_putchar_fd ('\n', 1);
		}
		if (data->pwd_old != NULL)
			free(data->pwd_old);
		data->pwd_old = ft_strdup(data->pwd_now);
		free(data->pwd_now);
		data->pwd_now = getcwd(NULL, 0);
		tmp_env = search_token_in_envp(data, "PWD");
		if (tmp_env != NULL)
		{
			ft_lstdelone(&tmp_env);
			ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("PWD=", data->pwd_now)));
		}
		tmp_env = NULL;
		tmp_env = search_token_in_envp(data, "OLDPWD");
		if (tmp_env == NULL)
		{
			ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("OLDPWD=", data->pwd_old)));
		}
		if (tmp_env != NULL)
		{
			ft_lstdelone(&tmp_env);
			ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("OLDPWD=", data->pwd_old)));
		}
		exit_exec(data, 0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(tmp->arg[1]);
		errno = 0;
		exit_exec(data, 1);
	}
	if (path != NULL)
		free(path);
}

void	export(t_data *data, t_info *tmp)
{
	char	**for_split;
	t_list	*tmp_env;


	if (tmp->arg[1] != NULL)
	{
		if (ft_isalpha(tmp->arg[1][0]) == 1 || tmp->arg[1][0] == '_')
		{
			for_split = ft_split(tmp->arg[1], '=');
			tmp_env = search_token_in_envp(data, for_split[0]);
			if (tmp_env == NULL)
			{
				ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(tmp->arg[1])));
			}
			else
			{
				ft_lstdelone(&tmp_env);
				ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(tmp->arg[1])));
			}
			split_free(for_split);
			exit_exec(data, 0);
		}
		else
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(tmp->arg[1], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			exit_exec(data, 1);
		}
	}
}

void	unset(t_data *data, t_info *tmp)
{
	char	**for_split;
	t_list	*tmp_env;


	if (tmp->arg[1] != NULL)
	{
		if (ft_isalpha(tmp->arg[1][0]) == 1 || tmp->arg[1][0] == '_')
		{
			for_split = ft_split(tmp->arg[1], '=');
			tmp_env = search_token_in_envp(data, for_split[0]);
			if (tmp_env != NULL)
				ft_lstdelone(&tmp_env);
			split_free(for_split);
			exit_exec(data, 0);
		}
		else
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(tmp->arg[1], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			exit_exec(data, 1);
		}
	}
}

void	tor_minishell(t_data *data, t_info *tmp) //доделать
{
	char	**env;
	pid_t	pid;

	env = NULL;
	increment_shell_in_env(data);
	env = env_list_to_map(data);
	decrement_shell_in_env(data);
	pid = fork();
	add_pid(data, pid);
	if (pid == 0)
		serch_bin(data, tmp, env);
	split_free(env);
}

void	exit_my(t_data *data, t_info *tmp)
{
	(void)tmp;
	ft_lstclear(&data->env);
	info_clear(&data->info);
	free(data->pid);
	if (data->pwd_old != NULL)
		free(data->pwd_old);
	free(data->pwd_now);
	free(data->pwd_home);
	free(data->pwd_start);
	exit(data->exit_proc_number);
}

void	exec_build_cmd(t_data *data, t_info *tmp)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		echo(data, tmp);
	if (ft_strcmp("cd", tmp->command) == 0)
		cd(data, tmp);
	if (ft_strcmp("pwd", tmp->command) == 0)
		pwd(data, tmp);
	if (ft_strcmp("export", tmp->command) == 0)
		export(data, tmp);
	if (ft_strcmp("unset", tmp->command) == 0)
		unset(data, tmp);
	if (ft_strcmp("env", tmp->command) == 0)
		env(data, tmp);
	if (ft_strcmp("exit", tmp->command) == 0)
		exit_my(data, tmp);
	if (ft_search_word_in_str_on_end(tmp->command, "/minishell") == 0)
		tor_minishell(data, tmp);
}

void	init_pid(t_data *data)
{
	int i;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * (info_size(data->info) + 1));
	if (!data->pid)
		exit (0);
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
		if (waitpid(data->pid[i], &data->exit_proc_number, 0) == -1)
		{
			return (perror("WAIT_PID"));
		}
		if (WIFSIGNALED(data->exit_proc_number)) {
			data->exit_proc_number = 130;
		}
		else
		{
			data->exit_proc_number = WEXITSTATUS(data->exit_proc_number);
		}
//		printf("exit status %d\n", data->exit_proc_number);
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
	if (pid != 0)
		data->pid[i] = pid;
}

char	*init_path_for_execve(t_data *data, t_info *info)
{
	int 	i;
	int		flag;
	char	**split;
	char	*path;
	char	*tmp_path;

	path = NULL;
	flag = 0;
	i = 0;
	if (info->command[0] == '/')
	{
		path = info->command;
		if (access(path, 0) == 0)
			flag = 1;
	}
	else if (info->command[0] == '.' && info->command[1] == '/')
	{
		tmp_path = ft_strtrim_start(info->command, ".");
		path = ft_strjoin(data->pwd_now, tmp_path);
		free(tmp_path);
		if (access(path, 0) == 0)
			flag = 1;
		else
		{
			free(path);
			path = NULL;
		}
	}
	else
	{
		tmp_path = ft_strjoin("/", info->command);
		split = NULL;
		split = ft_split(search_in_envp(data, "PATH"), ':');
		while (split[i] )
		{
			path = ft_strjoin(split[i], tmp_path);
			if (access(path, 0) == 0)
			{
				flag = 1;
				break ;
			}
			i++;
			free(path);
			path = NULL;
		}
		free(tmp_path);
		split_free(split);
	}
	if (flag == 0)
		return (NULL);
	return (path);
}

void	serch_bin(t_data *data, t_info *info, char **env)
{
	char	*path;

	path = init_path_for_execve(data, info);
	if (path != NULL)
		data->exit_proc_number = execve(path, info->arg, env);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->command, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
}

void	exec_bin(t_data *data, t_info *info)
{
	serch_bin(data, info, data->envp);
	exit (data->exit_proc_number);
}

int init_pipe_size(t_info *tmp)
{
    int i;

    i = 0;
    while (tmp != NULL)
    {
        if (tmp->pipe == 1)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

int	init_redirect_file_for_in(t_data *data, t_info *info, int flag_fork)
{
	int i;
	int	filein;

	filein = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "2") == 0)
			filein = open_file(data, info->red[i+1], 2, flag_fork);
		else
			break ;
		i+=2;
	}
	return (filein);
}

int	init_redirect_file_for_out(t_data *data, t_info *info, int flag_fork)
{
	int i;
	int fileout;

	fileout = -1;
	i = 0;
	while (info->red[i])
	{
		if (ft_strcmp(info->red[i], "1") == 0)
			fileout = open_file(data, info->red[i+1], 1, flag_fork);
		if (ft_strcmp(info->red[i], "3") == 0)
			fileout = open_file(data, info->red[i+1], 0, flag_fork);
		if (fileout != -1 && info->red[i+2] != NULL && ((ft_strcmp(info->red[i+2], "1") == 0) || (ft_strcmp(info->red[i+2], "3") == 0)))
			close(fileout);
		i+=2;
	}
	return (fileout);
}

void	init_redirect(t_data *data, t_info *info, int flag_fork, int flag_in)
{
	int	filein;
	int fileout;

	if ((info->red != NULL && ft_strcmp(info->red[0], "2") == 0) && flag_in == 1)
	{
		filein = init_redirect_file_for_in(data, info, flag_fork);
		if (filein != -1)
		{
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
	}
	if (info->red != NULL)
	{
		fileout = init_redirect_file_for_out(data, info, flag_fork);
		if (fileout != -1)
		{
			dup2(fileout, STDOUT_FILENO);
			close(fileout);
		}
	}
}

void	exec_cmd_one(t_data *data, t_info *info)
{
	pid_t	pid;

	if (check_on_bild_cmd(info) == 1)
	{
		init_redirect(data, info, 0, 0);
		exec_build_cmd(data, info);
		dup2(data->std_out, STDOUT_FILENO);
	}
	else
	{
		pid = fork();
		add_pid(data, pid);
		if (pid == 0)
		{
			init_redirect(data, info, 1, 1);
			exec_bin(data, info);
		}
	}
}

void	exec(t_data *data)
{
	t_info *tmp;
	pid_t	pid;

	(void)pid;
	tmp = data->info;
	data->pipe_size = init_pipe_size(tmp);
	while (tmp != NULL)
	{

//		if (check_on_bild_cmd(tmp) == 1 && tmp->pipe == 0 && tmp->red == NULL)
//		{
//			exec_build_cmd(data, tmp);
//		}
//		else if (tmp->pipe == 0 && tmp->red == NULL)
//		{
//			pid = fork();
//			if (pid == -1) {
//				return ;
//			}
//			add_pid(data, pid);
//			if (pid == 0)
//			{
//				exec_bin(data, tmp);
//			}
//		}
		if (tmp->pipe == 0)
			exec_cmd_one(data, tmp);
		else if (tmp->pipe == 1)
			tmp = exec_pipe_redirect(data, tmp);
		tmp = tmp->next;
	}
}
// echo -nnnnnnnn hi
// echo asdsdasdas | pwd
void    plug(t_data *data)
{
 	t_info *tmp;
	(void)tmp;

	info_add_back(&data->info, info_new());
	tmp = data->info;
	data->info->command = "cat";
	data->info->count_command = 0;
	data->info->arg = ft_split("cat -e", ' ');
	data->info->flag = 0;
	data->info->red = ft_split("2 1 2 2 2 3 2 4", ' ');
	data->info->semocolon = 0;
	data->info->pipe = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "head";
//	tmp->count_command = 1;
//	tmp->arg = ft_split("head", ' ');
//	tmp->flag = 0;
//	tmp->red = NULL;
//	tmp->pipe = 1;
//	tmp->semocolon = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "head";
//	tmp->count_command = 3;
//	tmp->arg = ft_split("head", ' ');
//	tmp->flag = 0;
//	tmp->red = NULL;
//	tmp->pipe = 1;
//	tmp->semocolon = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "head";
//	tmp->count_command = 3;
//	tmp->arg = ft_split("head", ' ');
//	tmp->flag = 0;
//	tmp->red = NULL;
//	tmp->pipe = 1;
//	tmp->semocolon = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "head";
//	tmp->count_command = 3;
//	tmp->arg = ft_split("head", ' ');
//	tmp->flag = 0;
//	tmp->red = NULL;
//	tmp->pipe = 1;
//	tmp->semocolon = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "cat";
//	tmp->count_command = 4;
//	tmp->arg = ft_split("cat -e", ' ');
//	tmp->flag = 0;
//	tmp->red = ft_split("1 1 1 2 1 3", ' ');
//	tmp->pipe = 0;
//	tmp->semocolon = 0;
//	info_add_back(&data->info, info_new());
//	tmp = tmp->next;
//	tmp->command = "pwd";
//	tmp->count_command = 3;
//	tmp->arg = ft_split("pwd", ' ');
//	tmp->flag = 0;
//	tmp->red = NULL;
//	tmp->pipe = 0;
//	tmp->semocolon = 0;
	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "grep";
	// tmp->count_command = 3;
	// tmp->arg = ft_split("grep HOME", ' ');
	// tmp->flag = 0;
	// tmp->red = NULL;
	// tmp->pipe = 0;
	// tmp->semocolon = 1;



	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "env";
	// tmp->count_command = 3;
	// tmp->arg = ft_split("env", ' ');
	// tmp->flag = 0;
	// tmp->red = NULL;
	// tmp->pipe = 0;
	// tmp->semocolon = 1;
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
//	int s;
	// char *str;
	
	ft_init_struct(&data, envp);
	// str = search_in_envp(&data, "PATH");
	// printf("%s\n", str);
	// free(str);
	//plug(&data);
//	// info_print_content(&data.info);
//	// printf("jfksdjksafdhj\n");
	// init_pid(&data);
	// exec(&data);
	// wait_pid(&data);
	// printf("pid %d\n", getpid());
	// pause();
	 while (data.status != 0)
	 {
		 data.str = readline(MINISHELL_MSG);
		 ft_parser(&data);
		init_pid(&data);
		exec(&data);
		wait_pid(&data);
		 info_clear(&data.info);
		 free(data.str);
	 }
//	free struct
    printf("%d", 1);
    //Test
	printf("fakkldsjk");



	 printf("eoqwiqeioqewioip");
   //ft_parser(&data);
}
