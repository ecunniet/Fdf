/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:24:09 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/14 23:24:08 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_countspace(int n)
{
	int nbspace;

	nbspace = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		nbspace++;
	while (n != 0)
	{
		n /= 10;
		nbspace++;
	}
	return (nbspace);
}

static char		*ft_strrev(char *str)
{
	char	buffer;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j + 1)
	{
		buffer = str[i];
		str[i] = str[j];
		str[j] = buffer;
		i++;
		j--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				space;
	unsigned int	j;

	i = 0;
	j = (n < 0) ? -n : n;
	space = ft_countspace(n) + 1;
	if (!(str = (char*)malloc(sizeof(char) * space)))
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (j != 0 && i < space)
	{
		str[i++] = (j % 10) + '0';
		j /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	str = ft_strrev(str);
	return (str);
}
