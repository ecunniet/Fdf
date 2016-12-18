/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 20:15:37 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/17 20:42:29 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst && (src + len) > dst)
	{
		while (len > 0)
		{
			((unsigned char*)dst)[len - 1] = ((unsigned char*)src)[len - 1];
			len--;
		}
		return (dst);
	}
	if (src == dst)
		return (dst);
	ft_memcpy(dst, src, len);
	return (dst);
}
