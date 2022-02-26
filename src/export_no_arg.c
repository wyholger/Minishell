#include "../include/minishell.h"

void	swap_token(t_list	*swap_token)
{
	if (swap_token->prev != NULL && swap_token->next != NULL && swap_token->next->next != NULL)
	{
		swap_token->next->prev = swap_token->prev;
		swap_token->prev->next = swap_token->next;
		swap_token->next->next->prev = swap_token;
		swap_token->prev = swap_token->next;
		swap_token->next = swap_token->next->next;
		swap_token->prev->next= swap_token;
	}
	else if (swap_token->prev == NULL && swap_token->next != NULL && swap_token->next->next != NULL)
	{
		swap_token->next->prev = swap_token->prev;
		swap_token->next->next->prev = swap_token;
		swap_token->prev = swap_token->next;
		swap_token->next = swap_token->next->next;
		swap_token->prev->next= swap_token;
	}
	else if (swap_token->prev != NULL && swap_token->next != NULL && swap_token->next->next == NULL)
	{
		swap_token->next->prev = swap_token->prev;
		swap_token->prev->next = swap_token->next;
		swap_token->prev = swap_token->next;
		swap_token->next = swap_token->next->next;
		swap_token->prev->next= swap_token;
	}
}

void 	print_env_for_export(t_list *lst)
{
	char	**split;

	while (lst != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		split = ft_split(lst->word, '=');
		ft_putstr_fd(split[0], 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(split[1], 1);
		ft_putstr_fd("\"\n", 1);
		split_free(split);
		lst = lst->next;
	}
}

void	sort_print_env(int size, t_list	*new)
{
	t_list	*tmp;

	while (size >= 0)
	{
		while (new->prev != NULL)
			new = new->prev;
		tmp = new;
		while (tmp != NULL && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->word, tmp->next->word) > 0)
			{
				swap_token(tmp);
				tmp = tmp->prev;
			}
			tmp = tmp->next;
		}
		size--;
	}
	while (new->prev != NULL)
		new = new->prev;
	print_env_for_export(new);
	ft_lstclear(&new);
}

void	export_if_no_arg(t_data *data)
{
	t_list	*tmp_env;
	t_list	*new;
	int		size;

	new = NULL;
	size = ft_lstsize(data->env);
	tmp_env = data->env;
	while (tmp_env != NULL)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp_env->word)));
		tmp_env = tmp_env->next;
	}
	sort_print_env(size, new);
}