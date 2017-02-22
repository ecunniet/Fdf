/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:28:43 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/05 22:25:21 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_pixel_put_image(t_env *list, int x, int y)
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

static void	ft_bresenham_y(t_env *list, t_line *bres)
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

static void	ft_bresenham_x(t_env *list, t_line *bres)
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

static void	ft_bresenham(t_env *list, int n, int i)
{
	t_line	bres;

	bres.xi = (i == 0) ? (int)((list->h + (n - 1))->x) :
	(int)((list->h + (n - (int)(list->xmax)))->x);
	bres.yi = (i == 0) ? (int)((list->h + (n - 1))->y + (list->h +
	(n - 1))->z + 0.5) : (int)((list->h + (n - (int)(list->xmax)))->y +
	(list->h + (n - (int)(list->xmax)))->z + 0.5);
	bres.xf = (int)((list->h + n)->x);
	bres.yf = (int)((list->h + n)->y + (list->h + n)->z + 0.5);
	bres.dx = abs(bres.xf - bres.xi);
	bres.dy = abs(bres.yf - bres.yi);
	bres.xinc = (bres.xf > bres.xi) ? 1 : -1;
	bres.yinc = (bres.yf > bres.yi) ? 1 : -1;
	ft_pixel_put_image(list, bres.xi, bres.yi);
	bres.i = 1;
	if (bres.dx > bres.dy)
		ft_bresenham_x(list, &bres);
	else
		ft_bresenham_y(list, &bres);
}

void		ft_call_bresenham(t_env *list, int i, int color, int v)
{
	int			tmp;
	int			j;

	if (v == 1 && list->rainbow == 1)
	{
		tmp = i / list->xmax;
		if (list->nblr < 1)
			list->color = *(list->r + tmp);
		else
		{
			j = (tmp / (list->nblr + 1) >= list->modr) ?
			(tmp - list->modr) / list->nblr : tmp / (list->nblr + 1);
			j = (j == 6) ? 5 : j;
			list->color = *(list->r + j);
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
