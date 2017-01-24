/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/24 18:42:47 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define IMG 600

void	ft_pixel_put_image(t_env *list, int x, int y, char code)
{
	int tmp;

	tmp = (x + (y * IMG)) + (((IMG / 2) * IMG) + (IMG / 2));
	if (tmp < IMG * IMG && tmp >= 0)
	{
		*(list->adi + (tmp * 4)) = code;
		*(list->adi + (1 + tmp * 4)) = code;
		*(list->adi + (2 + tmp * 4)) = code;
	}
}

void	ft_matrice(t_env *list, int i, int x, int y)
{
	int		z;
	double	angle;

	z = (x == 0 && y == 0) ? 1 : 0;
	angle = (x == 1) ? (list->angle_x * (M_PI / 180)) : -1;
	angle = (y == 1 && angle == -1) ? (list->angle_y * (M_PI / 180)) : angle;
	angle = (z == 1 && angle == -1) ? (list->angle_z * (M_PI / 180)) : angle;
	(list->h + i)->x = ((list->tmp + i)->x * ((x * x) + (1 - (x * x)) *
	cos(angle))) + ((list->tmp + i)->y * (x * y * (1 - cos(angle)) - z *
	sin(angle))) + ((list->tmp + i)->z * (x * z * (1 - cos(angle)) + y *
	sin(angle)));
	(list->h + i)->y = ((list->tmp + i)->x * (x * y * (1 - cos(angle)) + z *
	sin(angle))) + ((list->tmp + i)->y * ((y * y) + (1 - (y * y)) *
	cos(angle))) + ((list->tmp + i)->z * (y * z * (1 - cos(angle)) - x *
	sin(angle)));
	(list->h + i)->z = ((list->tmp + i)->x * (x * z * (1 - cos(angle)) - y *
	sin(angle))) + ((list->tmp + i)->y * (y * z * (1 - cos(angle)) + x *
	sin(angle))) + ((list->tmp + i)->z * ((z * z) + (1 - (z * z)) *
	cos(angle)));
}

void	ft_mid_zoom_ptp(t_env *list, int i, int code)
{
	if (code == 0)
		while (i < list->xmax * list->ymax)
		{
			(list->tmp + i)->x = ((list->p + i)->x - list->xmax / 2) * 10;
			(list->tmp + i)->y = (list->p + i)->y;
			(list->tmp + i)->z = ((list->p + i)->z - list->ymax / 2) * 10;
			i++;
		}
	else
	{
		(list->tmp + i)->x = (list->h + i)->x;
		(list->tmp + i)->y = (list->h + i)->y;
		(list->tmp + i)->z = (list->h + i)->z;
	}
}

int		ft_fill_image(t_env *list)
{
	int		i;

	ft_mid_zoom_ptp(list, 0, 0);
	i = 0;
	while (i < list->xmax * list->ymax)
	{
		ft_matrice(list, i, 1, 0);
		ft_mid_zoom_ptp(list, i, 1);
		ft_matrice(list, i, 0, 1);
		ft_mid_zoom_ptp(list, i, 2);
		ft_matrice(list, i, 0, 0);
		ft_pixel_put_image(list, (list->h + i)->x,
		(list->h + i)->y + (list->h + i)->z + 0.5, 255);
		i++;
	}
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	i--;
	while (i >= 0)
	{
		ft_pixel_put_image(list, (list->h + i)->x,
		(list->h + i)->y + (list->h + i)->z + 0.5, 0);
		i--;
	}
	return (0);
}

int		ft_key_funct(int keycode, t_env *list)
{
	printf("keycode event %d\ntaille de l'angle: %f\n", keycode, list->angle_x);
	list->angle_x = (keycode == 123) ? (list->angle_x + 1) : list->angle_x;
	list->angle_x = (keycode == 124) ? (list->angle_x - 1) : list->angle_x;
	list->angle_y = (keycode == 126) ? (list->angle_y + 1) : list->angle_y;
	list->angle_y = (keycode == 125) ? (list->angle_y - 1) : list->angle_y;
	list->angle_z = (keycode == 69) ? (list->angle_z + 1) : list->angle_z;
	list->angle_z = (keycode == 78) ? (list->angle_z - 1) : list->angle_z;
	return (0);
}

int		ft_draw_pix(t_env *list)
{
	list->angle_x = 0;
	list->angle_y = 0;
	list->angle_z = 0;
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
	if (!(list->tmp = (t_pixel*)malloc(sizeof(t_pixel)
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
			(list->p + i)->y = -ft_atoi(point[x]);
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
