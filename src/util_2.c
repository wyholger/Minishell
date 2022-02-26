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
