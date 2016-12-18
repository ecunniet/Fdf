/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:21:06 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/16 14:14:35 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (!(mem = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size + 1)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
