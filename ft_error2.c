/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:20:31 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/25 16:30:20 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_verif_x(int xmax_new, int xmax_old)
{
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (xmax_old == -1 && xmax_new == 0)
		ft_error(2, 0);
	else if (xmax_old == -1 && xmax_new > 0)
		return (xmax_new);
	else if (xmax_new != xmax_old)
		ft_error(3, 0);
	return (xmax);
}

void		ft_error(int i, char *str)
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
	if (i == 4)
		ft_putstr("Fail to close file\n");
	exit(EXIT_FAILURE);
}
