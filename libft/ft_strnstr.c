/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:40:24 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/16 13:08:39 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	z;

	i = 0;
	j = ft_strlen(s2);
	z = 0;
	if (j == 0)
		return ((char*)s1);
	while (s1[z] != '\0' && z < len)
	{
		if (s1[z] == s2[i])
		{
			while (s1[z + i] == s2[i] && i < j && z + i < len)
				i++;
			if (i == j)
				return ((char*)(s1 + z));
			else
				i = 0;
		}
		z++;
	}
	return (NULL);
}
