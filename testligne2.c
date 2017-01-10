/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testligne2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 19:58:01 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/10 18:14:23 by ecunniet         ###   ########.fr       */
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
	int err;
	int e2;
	int x;
	int y;
	int xinc;
	int yinc;
	int i;

	x = xi;
	y = yi;
	dx = ABS(xf - xi);
	dy = ABS(yf - yi);
	xinc = (xf > yi) ? 1 : -1;
	yinc = (yf > yi) ? 1 : -1;
	err = ((dx < dy) ? dx : -dy)/2;
	while (true)
	{
	*(e->adi + (x + y * 100) * 4) = 255;
	*(e->adi + 1 + (x + y * 100) * 4) = 255;
	*(e->adi + 2 + (x + y * 100) * 4) = 255;
	if (x == xf && y == yf)
		return ;
	e2 = err;
	if (e2 > -dx)
	{
		err -= dy;
		x += xinc;
	}
	if (e2 < dy)
	{
		err += dx;
		y += yinc;
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
	line(10, 100, 10, 70, &e);
	mlx_put_image_to_window(mlx, win, img_ptr, 25, 25);
	mlx_loop(mlx);
	return (0);
}

int main(void)
{
	ft_draw_pix();
	return (0);
}
