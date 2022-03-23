/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpitts <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:45:59 by wpitts            #+#    #+#             */
/*   Updated: 2022/03/23 18:46:05 by wpitts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *src)
{
	size_t	i;
	char	*dst;
	size_t	len;

	len = ft_strlen(src);
	dst = malloc(len + 1);
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
