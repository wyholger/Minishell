#include "libft.h"

char	*ft_strcpy(char *src)
{
	size_t	i;
	char	*dst;
	size_t	len;
	
	len = ft_strlen(src);
	dst = malloc( len + 1);
	i = 0;
	if (!src || !dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


//
// Created by wyholger on 24.12.2021.
//

