/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/16 21:58:43 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define IMG 600

void	ft_pixel_put_image(t_env *list, int x, int y)
{
	int tmp;

	tmp = (x + (y * IMG)) * 8 + ((IMG / 2) * (IMG / 2)) + IMG / 3;
	if (tmp < IMG * IMG && tmp >= 0)
	{
		*(list->adi + (tmp * 4))= 255;
		*(list->adi + (1 + tmp * 4)) = 255;
		*(list->adi + (2 + tmp * 4)) = 255;
	}
}

void	ft_matrice(t_env *list, int i)
{
	(list->h + i)->x = 1 * (list->p + i)->x;
	(list->h + i)->y = ((list->p + i)->y * cos(list->angle * (M_PI / 180))) 
	- ((list->p + i)->z * sin(list->angle * (M_PI / 180)));
	(list->h + i)->z = ((list->p + i)->y * sin(list->angle * (M_PI / 180)))
	+ ((list->p + i)->z * cos(list->angle * (M_PI / 180)));
	/*
	x = (x*cos(e->angle * (M_PI / 180))) + (z*sin(e->angle * (M_PI / 180))) + 0.5;
	y = 1*y + 0.5;
	z = -(x*sin(e->angle * (M_PI / 180))) + (z*cos(e->angle * (M_PI / 180))) + 0.5;
	*/
}

int		ft_fill_image(t_env *list)
{
	int		i;

	i = 0;
	while (i < list->xmax * list->ymax)
	{
		ft_matrice(list, i);
		ft_pixel_put_image(list, (list->h + i)->x + 0.5, ((list->h + i)->y + 0.5 * (list->h + i)->z) + 0.5);
		i++;
	}
	return (0);
}

int		ft_key_funct(int keycode, t_env *list)
{
	printf("keycode event %d\ntaille de l'angle: %d\n", keycode, list->angle);
	if (keycode == 123)
		list->angle += 5;
	if (keycode == 124)
		list->angle -= 5;
	return (0);
}

int		ft_draw_pix(t_env *list)
{
	list->angle = 0;
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, IMG, IMG, "mlx_42");
	list->img_ptr = mlx_new_image(list->mlx, IMG, IMG);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_key_hook(list->win, ft_key_funct, list);
	mlx_loop_hook(list->mlx, ft_fill_image, list);
	mlx_loop(list->mlx);
	return (0);
}

void	ft_location(t_env *list, int i)
{
	int		y;
	int		x;
	char	**point;

	y = 0;
	if (!(list->p = (t_point*)malloc(sizeof(t_point)
	* (list->ymax * list->xmax))))
		return ;
	if (!(list->h = (t_pixel*)malloc(sizeof(t_pixel)
	* (list->ymax * list->xmax))))
		return ;
	while (get_next_line(list->fd, &list->line))
	{
		point = ft_strsplit(list->line, ' ');
		x = 0;
		while (x < list->xmax)
		{
			(list->p + i)->z = y;
			(list->p + i)->x = x;
			(list->p + i)->y = ft_atoi(point[x]);
			x++;
			i++;
		}
		free(list->line);
		ft_ptrchardel(&point, list->xmax);
		y++;
	}
}

void	ft_get_pix(char *filename, t_env *list)
{
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_strsplit(list->line, ' '), list->xmax);
			free(list->line);
			list->ymax++;
		}
		if (close(list->fd) == 0)
		{
			if ((list->fd = open(filename, O_RDONLY)))
			{
				ft_location(list, 0);
				if (close(list->fd) == -1)
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
