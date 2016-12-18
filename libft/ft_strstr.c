/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:14:54 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/16 12:42:52 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int	i;
	int	j;
	int z;

	i = ft_strlen(little);
	j = 0;
	z = 0;
	if (i == 0)
		return ((char*)big);
	while (big[j] != '\0')
	{
		if (big[j] == little[z])
		{
			while (big[j + z] == little[z] && z < i)
				z++;
			if (z == i)
				return ((char*)(big + j));
			else
				z = 0;
		}
		j++;
	}
	return (NULL);
}
