/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:38:38 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/05 22:26:07 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_matrice(t_env *list, int i, int x, int y)
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

static void	ft_mid_zoom_ptp(t_env *list, int i, int code)
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

int			ft_key_funct(int keycode, t_env *list)
{
	list->angle_x = (keycode == 123) ? (list->angle_x - 1) : list->angle_x;
	list->angle_x = (keycode == 124) ? (list->angle_x + 1) : list->angle_x;
	list->angle_y = (keycode == 126) ? (list->angle_y - 1) : list->angle_y;
	list->angle_y = (keycode == 125) ? (list->angle_y + 1) : list->angle_y;
	list->angle_z = (keycode == 258) ? (list->angle_z - 1) : list->angle_z;
	list->angle_z = (keycode == 44) ? (list->angle_z + 1) : list->angle_z;
	list->zoom = (keycode == 24) ? (list->zoom + 0.2) : list->zoom;
	list->zoom = (keycode == 27 && list->zoom > 0.3) ? (list->zoom - 0.2)
	: list->zoom;
	if (keycode == 53)
		ft_free_struct(list);
	list->b_x = (keycode == 18) ? 1 : list->b_x;
	list->b_x = (keycode == 21) ? 0 : list->b_x;
	list->b_y = (keycode == 19) ? 1 : list->b_y;
	list->b_y = (keycode == 23) ? 0 : list->b_y;
	list->b_z = (keycode == 20) ? 1 : list->b_z;
	list->b_z = (keycode == 22) ? 0 : list->b_z;
	list->rainbow = (keycode == 15) ? 1 : list->rainbow;
	list->rainbow = (keycode == 17) ? 0 : list->rainbow;
	return (0);
}

int			ft_mouse_funct(int button, int x, int y, t_env *list)
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

int			ft_fill_image(t_env *list)
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
