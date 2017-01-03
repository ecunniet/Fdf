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
/*
int		my_key_funct(int keycode, t_mix e structure avec plusieurs param?)
{
	printf("keycode event %d\n", keycode);
	mlx_pixel_put(e->mlx, e->win, 300, 300, 0xFF00FF);
	return (0);
}*/

int		ft_draw_pix(t_env *list)
{
	int i;

	i = 0;
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, 400, 400, "mlx_42");
	while (i < list->xmax)
	{
		mlx_pixel_put(list->mlx, list->win, *(list->x + i) , *(list->y + i), 0x00FFFFFF);
		i++;
	}
//	mlx_key_hook(e.win, my_key_funct, &e);
	mlx_loop(list->mlx);
	return (0);
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
	if (!(list->y = (int*)malloc(sizeof(int) * (list->xmax * list->ymax))))
		return ;
	if (!(list->x = (int*)malloc(sizeof(int) * (list->xmax * list->ymax))))
		return ;
	if (!(list->z = (int*)malloc(sizeof(int) * (list->xmax * list->ymax))))
		return ;
	while (get_next_line(fd, &list->line))
	{
		point = ft_strsplit(list->line, ' ');
		while (x < list->xmax)
		{
			*(list->y + i) = y;
			*(list->x + i) = x;
			*(list->z + i) = ft_atoi(point[x]);
			x++;
			i++;
		}
		x = 0;
		free(list->line);
		ft_ptrchardel(&point, list->xmax);
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
		{
			if ((fd = open(filename, O_RDONLY)))
			{
				ft_location(fd, list);
				if (close(fd) == -1)
					ft_error(4, 0);
			}
		}
		else
			ft_error(4, 0);
	}
	else
		ft_error(1, filename);
}

int		main(int argc, char **argv)
{
	t_env	list;

	if (argc == 2)
	{
		ft_get_pix(argv[1], &list);
		ft_draw_pix(&list);
	}
	else
		ft_error(0, 0);
	return (0);
}
