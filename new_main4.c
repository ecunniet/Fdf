/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/02 21:39:32 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 1500
#define HEIGHT 1000
#define ABS(Value) ((Value < 0) ? -(Value) : (Value))

void	ft_pixel_put_image(t_env *list, int x, int y)
{
	int tmp;

	if (list->center_x == -1 && list->center_y == -1)
	{
		tmp = (x + (y * WIDTH)) + (((HEIGHT / 2) * WIDTH) + (WIDTH / 2));
		if (x + WIDTH / 2 < WIDTH && y + HEIGHT / 2 < HEIGHT &&
		y + HEIGHT / 2 >= 0 && x + WIDTH / 2 >= 0)
			*(((int*)list->adi) + tmp) = list->color;
	}
	else
	{
		tmp = (x + (y * WIDTH)) + ((list->center_y * WIDTH) + list->center_x);
		if (x + list->center_x < WIDTH && y + list->center_y < HEIGHT &&
		y + list->center_y >= 0 && x + list->center_x >= 0)
			*(((int*)list->adi) + tmp) = list->color;
	}
}

void	ft_bresenham_y(t_env *list, t_line *bres)
{
	bres->err = bres->dy / 2;
	while (bres->i <= bres->dy)
	{
		bres->yi += bres->yinc;
		bres->err += bres->dx;
		if (bres->err >= bres->dy)
		{
			bres->err -= bres->dy;
			bres->xi += bres->xinc;
		}
		ft_pixel_put_image(list, bres->xi, bres->yi);
		bres->i++;
	}
}

void	ft_bresenham_x(t_env *list, t_line *bres)
{
	bres->err = bres->dx / 2;
	while (bres->i <= bres->dx)
	{
		bres->xi += bres->xinc;
		bres->err += bres->dy;
		if (bres->err >= bres->dx)
		{
			bres->err -= bres->dx;
			bres->yi += bres->yinc;
		}
		ft_pixel_put_image(list, bres->xi, bres->yi);
		bres->i++;
	}
}

void	ft_bresenham(t_env *list, int n, int i)
{
	t_line	bres;

	bres.xi = (i == 0) ? (int)((list->h + (n - 1))->x) :
	(int)((list->h + (n - (int)(list->xmax)))->x);
	bres.yi = (i == 0) ? (int)((list->h + (n - 1))->y + (list->h +
	(n - 1))->z + 0.5) : (int)((list->h + (n - (int)(list->xmax)))->y +
	(list->h + (n - (int)(list->xmax)))->z + 0.5);
	bres.xf = (int)((list->h + n)->x);
	bres.yf = (int)((list->h + n)->y + (list->h + n)->z + 0.5);
	bres.dx = ABS(bres.xf - bres.xi);
	bres.dy = ABS(bres.yf - bres.yi);
	bres.xinc = (bres.xf > bres.xi) ? 1 : -1;
	bres.yinc = (bres.yf > bres.yi) ? 1 : -1;
	ft_pixel_put_image(list, bres.xi, bres.yi);
	bres.i = 1;
	if (bres.dx > bres.dy)
		ft_bresenham_x(list, &bres);
	else
		ft_bresenham_y(list, &bres);
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
			(list->tmp + i)->x = ((list->p + i)->x - list->xmax / 2)
			* 10 * list->zoom;
			(list->tmp + i)->y = (list->p + i)->y * list->zoom;
			(list->tmp + i)->z = ((list->p + i)->z - list->ymax / 2)
			* 10 * list->zoom;
			i++;
		}
	else
	{
		(list->tmp + i)->x = (list->h + i)->x;
		(list->tmp + i)->y = (list->h + i)->y;
		(list->tmp + i)->z = (list->h + i)->z;
	}
}

int		ft_key_funct(int keycode, t_env *list)
{
	printf("keycode event %d\ntaille de l'angle: %f\n", keycode, list->angle_y);
	list->angle_x = (keycode == 123) ? (list->angle_x - 1) : list->angle_x;
	list->angle_x = (keycode == 124) ? (list->angle_x + 1) : list->angle_x;
	list->angle_y = (keycode == 126) ? (list->angle_y - 1) : list->angle_y;
	list->angle_y = (keycode == 125) ? (list->angle_y + 1) : list->angle_y;
	list->angle_z = (keycode == 69) ? (list->angle_z - 1) : list->angle_z;
	list->angle_z = (keycode == 78) ? (list->angle_z + 1) : list->angle_z;
	list->zoom = (keycode == 67) ? (list->zoom + 0.2) : list->zoom;
	list->zoom = (keycode == 75 && list->zoom > 0.3) ? (list->zoom - 0.2)
	: list->zoom;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	list->b_x = (keycode == 279) ? 1 : list->b_x;
	list->b_x = (keycode == 117) ? 0 : list->b_x;
	list->b_y = (keycode == 115) ? 1 : list->b_y;
	list->b_y = (keycode == 119) ? 0 : list->b_y;
	list->b_z = (keycode == 116) ? 1 : list->b_z;
	list->b_z = (keycode == 121) ? 0 : list->b_z;
	list->rainbow = (keycode == 15) ? 1 : list->rainbow;
	list->rainbow = (keycode == 17) ? 0 : list->rainbow;
	return (0);
}

int		ft_mouse_funct(int button, int x, int y, t_env *list)
{
	if (button == 1)
	{
		list->center_x = x;
		list->center_y = y;
	}
	if (button == 2)
	{
		list->b_x = 0;
		list->b_y = 0;
		list->b_z = 0;
		list->angle_x = 15;
		list->angle_y = 25;
		list->angle_z = 0;
		list->center_x = -1;
		list->center_y = -1;
		list->zoom = 1;
		list->rainbow = 0;
	}
	return (0);
}

void	ft_call_bresenham(t_env *list, int i, int color, int v)
{
	int			tmp;
	int			j;

	if (v == 1 && list->rainbow == 1)
	{
		tmp = i / list->xmax;
		if (list->nblR < 1)
			list->color = *(list->R + tmp);
		else
		{
			j = (tmp / (list->nblR + 1) >= list->modR) ?
			(tmp - list->modR) / list->nblR : tmp / (list->nblR + 1);
			j = (j == 6) ? 5 : j;
			list->color = *(list->R + j);
		}
	}
	else
		list->color = color;
	if (i == 0)
		ft_pixel_put_image(list, (list->h + i)->x,
		(list->h + i)->y + (list->h + i)->z + 0.5);
	if (i % (int)(list->xmax) != 0)
		ft_bresenham(list, i, 0);
	if (i >= list->xmax)
		ft_bresenham(list, i, 1);
}

int		ft_fill_image(t_env *list)
{
	int		i;

	ft_mid_zoom_ptp(list, 0, 0);
	i = 0;
	list->angle_x = (list->b_x == 1) ? (list->angle_x + 1) : list->angle_x;
	list->angle_y = (list->b_y == 1) ? (list->angle_y + 1) : list->angle_y;
	list->angle_z = (list->b_z == 1) ? (list->angle_z + 1) : list->angle_z;
	while (i < list->xmax * list->ymax)
	{
		ft_matrice(list, i, 1, 0);
		ft_mid_zoom_ptp(list, i, 1);
		ft_matrice(list, i, 0, 1);
		ft_mid_zoom_ptp(list, i, 2);
		ft_matrice(list, i, 0, 0);
		ft_call_bresenham(list, i, 0xFFFFFF, 1);
		i++;
	}
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	while (--i >= 0)
		ft_call_bresenham(list, i, 0x00000, 2);
	return (0);
}

void	ft_initrainbow(t_env *list)
{
	list->rainbow = 0;
	if (!(list->R = (int*)malloc(sizeof(int) * 6)))
		exit(EXIT_FAILURE);
	*(list->R) = 0xf40000;
	*(list->R + 1) = 0xffa500;
	*(list->R + 2) = 0xf4f400;
	*(list->R + 3) = 0x00f400;
	*(list->R + 4) = 0x0028f4;
	*(list->R + 5) = 0xa300f4;
	list->nblR = (int)(list->ymax) / 6;
	list->modR = (int)(list->ymax) % 6;
}

int		ft_draw_pix(t_env *list)
{
	list->zoom = 1;
	list->angle_x = 15;
	list->angle_y = 25;
	list->angle_z = 0;
	list->center_x = -1;
	list->center_y = -1;
	ft_initrainbow(list);
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, WIDTH, HEIGHT, "mlx_42");
	list->img_ptr = mlx_new_image(list->mlx, WIDTH, HEIGHT);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_key_hook(list->win, ft_key_funct, list);
	mlx_mouse_hook(list->win, ft_mouse_funct, list);
	mlx_loop_hook(list->mlx, ft_fill_image, list);
	mlx_loop(list->mlx);
	return (0);
}

char	*ft_strmydup(char const *s1, char c)
{
	char	*s2;
	size_t	i;

	i = 0;
	while (s1[i] != c && s1[i] != '\0')
		i++;
	if (!(s2 = (char*)malloc(sizeof(char) * (i + 1))))
	{
		write(1, "pb malloc.\n", 9);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (s1[i] != c && s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_mysplit(char *s, char c, int nbword)
{
	int		z;
	int		j;

	z = 0;
	j = 0;
	while (j < nbword && s[z] != '\0')
	{
		if (s[z] != c && (s[z + 1] == c || s[z + 1] == '\0'))
			j++;
		z++;
	}
	z--;
	while (s[z] != c && z >= 0)
		if (--z < 0)
			break ;
	z++;
	return (ft_strmydup(s + z, c));
}

void	ft_location(t_env *list, int i, int x, int y)
{
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
		x = 0;
		while (x < list->xmax)
		{
			list->str = ft_mysplit(list->line, ' ', x + 1);
			(list->p + i)->z = y;
			(list->p + i)->x = x;
			(list->p + i)->y = -ft_atoi(list->str);
			free(list->str);
			x++;
			i++;
		}
		free(list->line);
		y++;
	}
}

int		ft_count_x(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (s == NULL)
		ft_error(2, 0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

void	ft_get_pix(char *filename, t_env *list)
{
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_count_x(list->line, ' '), list->xmax);
			free(list->line);
			list->ymax++;
		}
		if (close(list->fd) == 0)
		{
			if ((list->fd = open(filename, O_RDONLY)))
			{
				ft_location(list, 0, 0, 0);
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
