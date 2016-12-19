/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/19 19:59:29 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

//compilation: cc -o mlx main.c -lmlx -framework OpenGL -framework AppKit

int		my_key_funct(int keycode, t_mix *e/*structure avec plusieurs param?*/)
{
	printf("keycode event %d\n", keycode);
	mlx_pixel_put(e->mlx, e->win, 300, 300, 0xFF00FF);
	return (0);
}

int	main(void)
{
	t_mlx	e;
	int		x;
	int		y;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 400, 400, "mlx_42");
	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 150)
		{
			mlx_pixel_put(e.mlx, e.win, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_key_hook(e.win, my_key_funct, &e);
	mlx_loop(e.mlx);
}

//////////////////////////////////////////////////////

t_address	*ft_location(char **point, int y, int xmax)
{	
	t_address	*pix;
	int			x;

	if (!(pix = (t_address*)malloc(sizeof(t_address))))
		return (NULL);
	if (!(pix->x = (int*)malloc(sizeof(int) * (xmax))))
		return (NULL);
	if (!(pix->z = (int*)malloc(sizeof(int) * (xmax))))
		return (NULL);
	x = 0;
	pix->y = y;
	while (point[x])
	{
		pix->x = x;
		pix->z = ft_atoi(point[x]);
		pix->next = NULL;
		x++;
	}
}

int		ft_get_pix(char *filename)
{
	int		fd;
	t_env	list;

	list.xmax = -1;
	list.ymax = 0;
	if ((fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(fd, &list.line))
		{
			list.ymax++;
			list.xmax = ft_verif_x(ft_strsplit(list.line, ' '), list.xmax);
			free(line);
		}
		if (close(fd) == 0)
			if ((fd = open(filename, O_RDONLY)))
				ft_location(fd, &list.line, xmax, ymax);
		else
			ft_error(4, 0);
	}
	else
		ft_error(1, argv[1]);
	return(0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		ft_get_pix(argv[1]);
	else
		ft_error(0, 0);
	return (0);
}
