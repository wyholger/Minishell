#include "../include/minishell.h"

t_info	*info_new()
{
	t_info	*begin;

	begin = (t_info *)malloc(sizeof(t_info));
	if (!begin)
		return (NULL);
	begin->next = NULL;
	begin->prev = NULL;
	begin->arg = NULL;
	begin->command = NULL;
	return (begin);
}

void	info_add_back(t_info **lst, t_info *new)
{
	t_info	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
	}
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new;
				new->prev = tmp;
				new->next = NULL;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	info_clear(t_info **lst)
{
	t_info	*temp;

	if (!lst)
		return (1);
	temp = *lst;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp)
			free(temp);
	}
	return (0);
}

int	info_print_content(t_info **lst)
{
	int		i;
	t_info	*iter;

	i = 0;
	iter = *lst;
	while (iter)
	{
		printf("cmd: %s; arg: %s; flag: %s;\n", iter->command, iter->arg, iter->flag);
		// ft_putstr_fd(iter->command, 1);
		// ft_putstr_fd(" Arg ", 1);
		// if (iter->prev)
		// ft_putstr_fd(iter->prev->word, 1);
		// ft_putchar_fd('\n', 1);
		iter = iter->next;
		i++;
	}
	return (i);
}

int	info_size(t_info *lst)
{
	int		i;
	t_info	*sizer;

	i = 0;
	sizer = lst;
	while (sizer)
	{
		i++;
		sizer = sizer->next;
	}
	return (i);
}
