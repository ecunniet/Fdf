/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 21:12:30 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/22 16:30:23 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_countword(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static size_t	ft_location(char const *s, char c, size_t i)
{
	int		z;
	size_t	j;

	z = 0;
	j = 0;
	while (j < i && s[z] != '\0')
	{
		if (s[z] != c && (s[z + 1] == c || s[z + 1] == '\0'))
			j++;
		z++;
	}
	z--;
	while (s[z] != c && z >= 0)
		z--;
	return (z + 1);
}

static char		*ft_strmydup(char const *s1, char c)
{
	char	*s2;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s1[j] == c)
		j++;
	while (s1[j + i] != c)
		i++;
	if (!(s2 = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[j + i] != c)
	{
		s2[i] = s1[j + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	nword;
	size_t	nletter;
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (s == NULL)
		return (NULL);
	nword = ft_countword(s, c);
	if (!(str = (char**)malloc(sizeof(char*) * (nword + 1))))
		return (NULL);
	while (i < nword)
	{
		nletter = ft_location(s, c, j);
		str[i] = ft_strmydup(s + nletter, c);
		i++;
		j++;
	}
	str[i] = NULL;
	return (str);
}
