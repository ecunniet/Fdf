/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/16 18:45:07 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define IMG 600

typedef	struct	s_add
{
	char	*adi;
	int		numpix;
	double	angle;
}				t_add;

void	ft_light_pixel(t_add *e)
{
	*(e->adi + e->numpix * 4) = 255;
	*(e->adi + 1 + e->numpix * 4) = 255;
	*(e->adi + 2 + e->numpix * 4) = 255;
}

void	ft_matrice(double x, double y, double z, t_add *e)
{
	x = 1*x + 0.5;
	y = (y*cos(e->angle * (M_PI / 180))) - (z*sin(e->angle * (M_PI / 180))) + 0.5;
	z = (y*sin(e->angle * (M_PI / 180))) + (z*cos(e->angle * (M_PI / 180))) + 0.5;
	/*
	x = (x*cos(e->angle * (M_PI / 180))) + (z*sin(e->angle * (M_PI / 180))) + 0.5;
	y = 1*y + 0.5;
	z = -(x*sin(e->angle * (M_PI / 180))) + (z*cos(e->angle * (M_PI / 180))) + 0.5;
	*/
	e->numpix = (int)x + (((int)y  + 0.2 * (int)z) * 100);
	ft_light_pixel(e);
}

int		ft_key_funct(int keycode, t_add *e)
{
	printf("keycode event %d.\n", keycode);
	if (keycode == 123)
		e->angle += 5;
	if (keycode == 124)
		e->angle -= 5;
	return (0);
}

int		ft_draw_pix()
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	t_add			e;

	width = 400;
	height = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_42");
	img_ptr = mlx_new_image(mlx, width, height);
	e.adi = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	e.angle = 45.00000;
	ft_matrice(10, 10, 10, &e);
	mlx_put_image_to_window(mlx, win, img_ptr, 50, 50);
	mlx_key_hook(win, ft_key_funct, &e);
	mlx_loop(mlx);
	return (0);
}

void	ft_pixel_put_image(t_img *img, int x, int y)
{
	int tmp;

	tmp = (x + (y * IMG)) * 8 + ((IMG / 2) * (IMG / 2)) + IMG / 3;
	if (tmp < IMG * IMG && tmp >= 0)
	{
		*(img->adi + (tmp * 4))= 255;
		*(img->adi + (1 + tmp * 4)) = 255;
		*(img->adi + (2 + tmp * 4)) = 255;
	}
}

void	ft_fill_image(t_env *list, t_img *img)
{
	int		i;

	i = 0;
	while (i < list->xmax * list->ymax)
	{
		ft_pixel_put_image(img, (list->p + i)->x, (list->p + i)->y + (list->p + i)->z + 0.5);
		i++;
	}
}

int		ft_draw_pix(t_env *list)
{
	t_img	img;

	img.width = IMG;
	img.height = IMG;
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, IMG, IMG, "mlx_42");
	img.img_ptr = mlx_new_image(list->mlx, img.width, img.height);
	img.adi = mlx_get_data_addr(img.img_ptr, &img.bpp,
	&img.size_line, &img.endian);
	ft_fill_image(list, &img);
	mlx_put_image_to_window(list->mlx, list->win, img.img_ptr, 0, 0);
//	mlx_key_hook(e.win, my_key_funct, &e);
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
