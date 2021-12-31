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

void	ft_init_struct(t_data *data, char **envp)
{
	(void)envp;
	data->status = 1;
	data->token = NULL;
	data->info = NULL;
	data->envp = envp;
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

void	echo(t_data *data, t_info *tmp)
{
	int i;

	i = 0;
	(void)data;
	if (tmp->pipe == 0 && tmp->red == 0)
	{
		if (tmp->arg != NULL)
		{
			while (tmp->arg[i])
			{
				write(1, tmp->arg[i], ft_strlen(tmp->arg[i]));
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
}

void	exec_build_cmd(t_data *data, t_info *tmp)
{
	if (ft_strcmp("echo", tmp->command) == 0)
		echo(data, tmp);
	// if (ft_strcmp("cd", tmp->command) == 0)
	// 	return (1);
	// if (ft_strcmp("pwd", tmp->command) == 0)
	// 	return (1);
	// if (ft_strcmp("export", tmp->command) == 0)
	// 	return (1);
	// if (ft_strcmp("unset", tmp->command) == 0)
	// 	return (1);
	// if (ft_strcmp("env", tmp->command) == 0)
	// 	return (1);	
	// if (ft_strcmp("exit", tmp->command) == 0)
	// 	return (1);
	// return (0);
}

void	init_pid(t_data *data)
{
	int i;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * (info_size(&data->info) + 1));
	if (!data->pid)
		exit (0); //add if 
	while (i <= info_size(&data->info))
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
			return (perror("WAIT_PID"));
		if (WIFSIGNALED(data->exit_proc_number))
			data->exit_proc_number = 130;
		else
			data->exit_proc_number = WEXITSTATUS(data->exit_proc_number);
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

void	exec(t_data *data)
{
	t_info *tmp;
	pid_t	pid;

	tmp = data->info;
	printf("size info %d\n", info_size(tmp));
	while (tmp != NULL)
	{
		if (check_on_bild_cmd(tmp) == 1)
			exec_build_cmd(data, tmp);
		else 
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
				signal(SIGINT, child_signal_handler);
			add_pid(data, pid);
			if (pid == 0)
			{
				
			}
		}

		tmp = tmp->next;
	}
}

void    plug(t_data *data)
{
	t_info *tmp;

	info_add_back(&data->info, info_new());
	tmp = data->info;
	data->info->command = "echo";
	data->info->count_command = 0;
	data->info->arg = ft_split("123 456", ' ');
	data->info->flag = 0;
	data->info->red = NULL;
	data->info->semocolon = 1;
	data->info->pipe = 0;
	info_add_back(&data->info, info_new());
	tmp = tmp->next;
	tmp->command = "ls";
	tmp->count_command = 1;
	tmp->arg = ft_split("1 32", ' ');
	tmp->flag = 0;
	tmp->red = NULL;
	tmp->pipe = 1;
	tmp->semocolon = 0;
	info_add_back(&data->info, info_new());
	tmp = tmp->next;
	tmp->command = "grep";
	tmp->count_command = 2;
	tmp->arg = ft_split("1", ' ');
	tmp->flag = 0;
	tmp->red = NULL;
	tmp->pipe = 0;
	tmp->semocolon = 1;
	// info_add_back(&data->info, info_new());
	// tmp = tmp->next;
	// tmp->command = "ls";
	// tmp->count_command = 3;
	// tmp->arg = ft_split("3", ' ');
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
	info_print_content(&data.info);
	exec(&data);
	// while (data.status != 0)
	// {
	// 	data.str = readline(MINISHELL_MSG);
	// 	split_str(&data);
	// 	//ft_parser
	// 	free(data.str);
	// }
	//free struct
}
