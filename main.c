/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/19 22:11:44 by ecunniet         ###   ########.fr       */
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

int		ft_draw_pix(t_env *list)
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

void	ft_location(int fd, t_env *list)
{
	int		y;
	int		x;
	int		i;
	char	**point;

	i = 0;
	y = 0;
	x = 0;
	if (!(list->y = (int*)malloc(sizeof(int) * (xmax * ymax))))
		return (NULL);
	if (!(list->x = (int*)malloc(sizeof(int) * (xmax * ymax))))
		return (NULL);
	if (!(list->z = (int*)malloc(sizeof(int) * (xmax * ymax))))
		return (NULL);
	while (get_next_line(fd, &list->line))
	{
		point = ft_strsplit(list->line, ' ');
		while (x < xmax)
		{
			list->(*y + i) = y;
			list->(*x + i) = x;
			list->(*z +	i) = ft_atoi(point[x]);
			x++;
			i++;
		}
		x = 0;
		free(list->line);
		ft_ptrchardel(&point, xmax);
		y++;
	}
}

void	ft_get_pix(char *filename, t_env *list)
{
	int		fd;

	list->xmax = -1;
	list->ymax = 0;
	if ((fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_strsplit(list->line, ' '), list->xmax);
			free(list->line);
			list->ymax++;
		}
		if (close(fd) == 0)
			if ((fd = open(filename, O_RDONLY)))
			{
				ft_location(fd, list);
				if (close(fd) == -1)
					ft_error(4, 0);
			}
		else
			ft_error(4, 0);
	}
	else
		ft_error(1, argv[1]);
}

int		main(int argc, char **argv)
{
	t_env	list;

	if (argc == 2)
		ft_get_pix(argv[1], &list);
		ft_draw_pix(&list);
	else
		ft_error(0, 0);
	return (0);
}
