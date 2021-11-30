#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*des;

	des = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (des == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1 && s1[i] != '\0')
	{
		des[i] = s1[i];
		i++;
	}
	while (s2 && s2[k] != '\0')
	{
		des[i] = s2[k];
		i++;
		k++;
	}
	free(s1);
	des[i] = '\0';
	return (des);
}

int	ft_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_to_n(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}
