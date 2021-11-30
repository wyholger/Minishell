#include "get_next_line.h"

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != '\n' )
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*ft_new_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (NULL);
	while (str && str[i] != '\0' && str[i] != '\n' )
		i++;
	line = malloc(sizeof(char) * (i + 1 + ft_check_str(str)));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_tmp(char *str)
{
	int		i;
	char	*tmp;
	int		k;

	k = 0;
	i = ft_len_to_n(str);
	if (str == NULL)
		return (NULL);
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (tmp == NULL)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i] != '\0')
		tmp[k++] = str[i++];
	tmp[k] = '\0';
	free(str);
	return (tmp);
}

int	ft_check_tmp(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*tmp;
	int			i;

	i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while ((ft_check_tmp(tmp)) == 0 && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		tmp = ft_strjoin(tmp, buf);
		if (ft_line(tmp))
			break ;
	}
	free(buf);
	line = ft_new_line(tmp);
	tmp = ft_new_tmp(tmp);
	return (line);
}
