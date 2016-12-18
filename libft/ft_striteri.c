/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:40:51 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/22 16:20:45 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int j;

	j = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[j] != '\0')
	{
		f(j, s + j);
		j++;
	}
}
