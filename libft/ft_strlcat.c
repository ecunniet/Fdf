/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:46:19 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/12 19:18:45 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t ret;
	size_t ret2;

	i = 0;
	j = 0;
	ret2 = ft_strlen(src) + size;
	ret = ft_strlen(dst) + ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	if (i < size && size > 0)
	{
		while (i + j < size - 1 && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (ret);
	}
	return (ret2);
}
