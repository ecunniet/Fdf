/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:20:31 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/18 23:17:41 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_verif_x(char **point, int xmax)
{
	int x;

	x = 0;
	if (point == NULL)
		ft_error(2, 0);
	while (point[x])
		x++;
	if (xmax == -1)
		xmax = x;
	else
		if (xmax != x)
			ft_error(3, 0);
	return (xmax);
}	

void		ft_error(int i, char str);
{
	if (i == 0)
		ft_putstr("Usage: ./fdf <filename> [ case_size z_size ]\n");
	if (i == 1)
	{
		ft_putstr("No file");
		ft_putstr(str);
		ft_putchar('\n');
	}
	if (i == 2)
		ft_putstr("No data found.\n");
	if (i == 3)
		ft_putstr("Found wrong line length. Exiting.\n");
	exit(EXIT_FAILURE);
}
