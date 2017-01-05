/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/05 15:11:28 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>

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
	t_img	img;

	img.width = 100;
	img.height = 100;
	ft_putendl("Hey");
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, 150, 150, "mlx_42");
	ft_putendl("fenetre");
	img.img_ptr = mlx_new_image(list->mlx, img.width, img.height);
	img.addr_img = mlx_get_data_addr(img.img_ptr, &img.bits_pp, &img.size_line, &img.endian);
	*(img.addr_img + 1) = 255;
	mlx_put_image_to_window(list->mlx, list->win, img.img_ptr, 25, 25);
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
	if (!(list->p = (t_point*)malloc(sizeof(t_point) * (list->ymax * list->xmax))))
		return ;
	ft_putendl("la c'est ok?");
	while (get_next_line(fd, &list->line))
	{
		point = ft_strsplit(list->line, ' ');
		while (x < list->xmax)
		{
			(list->p + i)->x = y;
			(list->p + i)->x = x;
			(list->p + i)->z = ft_atoi(point[x]);
			x++;
			i++;
		}
		x = 0;
		free(list->line);
		ft_putendl("bla");
		ft_ptrchardel(&point, list->xmax);
		y++;
	}
	ft_putendl("end la c'est ok?");
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
