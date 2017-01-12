/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testligne2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:58:01 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/12 16:42:06 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#define ABS(Value) ((Value < 0) ? -(Value) : (Value))

typedef	struct	s_add
{
	char	*adi;
}				t_add;

void	ft_light_pixel(int x, int y, t_add *e)
{
	*(e->adi + (x + y * 400) * 4) = 255;
	*(e->adi + 1 + (x + y * 400) * 4) = 255;
	*(e->adi + 2 + (x + y * 400) * 4) = 255;
}

void line(int xi, int yi, int xf, int yf, t_add *e)
{
	int dx;
	int dy;
	int err;
	int x;
	int y;
	int xinc;
	int yinc;
	int i;

	x = xi;
	y = yi;
	dx = ABS(xf - xi);
	dy = ABS(yf - yi);
	xinc = (xf > xi) ? 1 : -1;
	yinc = (yf > yi) ? 1 : -1;
	ft_light_pixel(x, y, e);
	i = 1;
	if (dx > dy)
	{
		err = dx / 2;
		while (i <= dx)
		{
			x += xinc;
			err += dy;
			if (err >= dx)
			{
				err -= dx;
				y += yinc;
			}
			ft_light_pixel(x, y, e);
			i++;
		}
	}
	else
	{
		err = dy / 2;
		while (i <= dy)
		{
			y += yinc;
			err += dx;
			if (err >= dy)
			{
				err -= dy;
				x += xinc;
			}
			ft_light_pixel(x, y, e);
			i++;
		}
	}
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
	int x;
	int y;

	width = 400;
	height = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_42");
	img_ptr = mlx_new_image(mlx, width, height);
	e.adi = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	y = 0;
	while (y < 400)
	{
		x = 0;
		while (x < 400)
		{
		line(200, 200, x, y, &e);
		x += 5;
		}
		y += 5;
	}
	mlx_put_image_to_window(mlx, win, img_ptr, 50, 50);
	mlx_loop(mlx);
	return (0);
}

int main(void)
{
	ft_draw_pix();
	return (0);
}
