#include "../include/minishell.h"

char	*cd_pre_process(t_data *data, t_info *tmp)
{
	char	*path;

	data->flag_old_pwd = 0;
	path = ft_strdup(tmp->arg[1]);
	if (path == NULL)
		path = ft_strdup(data->pwd_home);
	if (ft_strcmp (path, "-") == 0)
	{
		if (data->pwd_old == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			exit_exec(data, 1);
			return (NULL);
		}
		else
		{
			free(path);
			path = NULL;
			path = ft_strdup(data->pwd_old);
			data->flag_old_pwd = 1;
		}
	}
	return (path);
}

void	cd_pwd_change(t_data *data)
{
	t_list	*tmp_env;

	tmp_env = search_token_in_envp(data, "PWD");
	if (tmp_env != NULL)
	{
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("PWD=", data->pwd_now)));
	}
	tmp_env = NULL;
	tmp_env = search_token_in_envp(data, "OLDPWD");
	if (tmp_env == NULL)
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("OLDPWD=", data->pwd_old)));
	if (tmp_env != NULL)
	{
		ft_lstdelone(&tmp_env);
		ft_lstadd_back(&data->env, ft_lstnew(ft_strjoin("OLDPWD=", data->pwd_old)));
	}
}

void	cd_process(t_data *data)
{
	if (data->flag_old_pwd == 1)
	{
		ft_putstr_fd (data->pwd_old, 1);
		ft_putchar_fd ('\n', 1);
	}
	if (data->pwd_old != NULL)
		free(data->pwd_old);
	data->pwd_old = ft_strdup(data->pwd_now);
	free(data->pwd_now);
	data->pwd_now = getcwd(NULL, 0);
}

void	cd(t_data *data, t_info *tmp)
{
	char	*path;

	path = cd_pre_process(data, tmp);
	if (path == NULL)
		return ;
	if (chdir(path) == 0)
	{
		cd_process(data);
		cd_pwd_change(data);
		exit_exec(data, 0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(tmp->arg[1]);
		errno = 0;
		exit_exec(data, 1);
	}
	free(path);
}

