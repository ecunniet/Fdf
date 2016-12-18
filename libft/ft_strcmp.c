/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:01:29 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/09 21:32:56 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i]
			&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
