/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/17 19:12:40 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_original.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define IMG 600

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
