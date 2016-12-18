/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 20:27:50 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/22 16:32:15 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		z;
	char	*str;

	if (s == NULL)
		return (NULL);
	j = ft_strlen(s) - 1;
	i = 0;
	z = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (!(i == j + 1))
	{
		while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
			j--;
	}
	if (!(str = (char*)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	while (i <= j && s[i] != '\0')
		str[z++] = s[i++];
	str[z] = '\0';
	return (str);
}
