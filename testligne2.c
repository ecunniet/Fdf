/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testligne2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:58:01 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/09 20:44:29 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#define ABS(Value) ((Value < 0) ? -(Value) : (Value))

typedef	struct	s_add
{
	char	*adi;
}				t_add;

void line(int xi, int yi, int xf, int yf, t_add *e)
{
	int dx;
	int dy;
	int cumul;
	int x;
	int y;
	int xinc;
	int yinc;
	int i;

	i = 1;
	x = xi;
	y = yi;
	dx = xf - xi;
	dy = yf - yi;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = ABS(dx);
	dy = ABS(dx);
	*(e->adi + (x + y * 100) * 4) = 255;
	*(e->adi + 1 + (x + y * 100) * 4) = 255;
	*(e->adi + 2 + (x + y * 100) * 4) = 255;
	if (dx < dy)
	{
		cumul = dx / 2;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul <= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			*(e->adi + (x  + y * 100) * 4) = 255;
			*(e->adi + 1 + (x + y * 100) * 4) = 255;
			*(e->adi + 2 + (x + y * 100) * 4) = 255;
			i++;
		}
	}
	else
	{
		cumul = dy / 2;
		while (i <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			*(e->adi + (x  + y * 100) * 4) = 255;
			*(e->adi + 1 + (x + y * 100) * 4) = 255;
			*(e->adi + 2 + (x + y * 100) * 4) = 255;
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

	width = 100;
	height = 100;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 150, 150, "mlx_42");
	img_ptr = mlx_new_image(mlx, width, height);
	e.adi = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	line(50, 50, 10, 70, &e);
	mlx_put_image_to_window(mlx, win, img_ptr, 25, 25);
	mlx_loop(mlx);
	return (0);
}

int main(void)
{
	ft_draw_pix();
	return (0);
}
