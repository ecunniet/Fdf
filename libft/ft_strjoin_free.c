/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:58:24 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/09 20:05:41 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char const *s1, char const *s2, int k)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL || k < 0 || k > 3)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	if (k == 1)
		free((void*)s1);
	if (k == 2)
		free((void*)s2);
	if (k == 3)
	{
		free((void*)s1);
		free((void*)s2);
	}
	return (str);
}
