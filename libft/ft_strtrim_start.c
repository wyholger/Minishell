#include "libft.h"

static char	*endcat(char const *str)
{
	size_t	pi;
	int		i;

	pi = ft_strlen(str) - 1;
	i = (int)pi;
	i++;
	return ((char *)str + i);
}

static char	*startcat(char const *str, char const *set)
{
	int		i;
	size_t	o;

	i = 0;
	o = 0;
	while (set[o])
	{
		if (str[i] == set[o])
		{
			o = 0;
			i++;
		}
		else
			o++;
	}
	return ((char *)str + i);
}

char	*ft_strtrim_start(char const *s1, char const *set)
{
	char	*strstart;
	char	*strend;
	int		len;
	char	*rezult;

	if (!s1 || !set)
		return (NULL);
	strstart = startcat(s1, set);
	strend = endcat(strstart);
	len = strend - strstart;
	if (strstart > strend)
	{
		rezult = malloc (sizeof(char) * 1);
		if (!rezult)
			return (NULL);
		rezult[0] = '\0';
		return (rezult);
	}
	rezult = ft_substr(s1, strstart - s1, len);
	if (!rezult)
		return (NULL);
	return (rezult);
}
