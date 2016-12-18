/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:20:31 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/13 18:11:48 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_error(int i, char str);
{
	if (i == 0)
		ft_putstr("Usage: ./fdf <filename> [ case_size z_size ]\n");
	if (i == 1)
	{
		ft_putstr("No file");
		ft_putstr(str);
	}
	if (i == 2)
		ft_putstr();
	return (2);
}
