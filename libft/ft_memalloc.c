/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 23:21:58 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/07 20:02:04 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	if (!(mem = (void*)malloc(sizeof(char) * size)))
		return (NULL);
	while (i < size)
	{
		((char*)mem)[i] = 0;
		i++;
	}
	return (mem);
}
