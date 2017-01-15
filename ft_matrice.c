/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 22:16:39 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/16 00:17:27 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minilibx/mlx.h"
#include <stdio.h>

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
	/*x = -1*x + 0.5;
	y = -(y*cos(e->angle * (M_PI / 180))) + z*sin(e->angle * (M_PI / 180)) + 0.5;
	z = -(y*sin(e->angle * (M_PI / 180))) - (z*cos(e->angle * (M_PI / 180))) + 0.5;
	*/
	x = (x*cos(e->angle * (M_PI / 180))) + (z*sin(e->angle * (M_PI / 180))) + 0.5;
	y = 1*y + 0.5;
	z = -(x*sin(e->angle * (M_PI / 180))) + (z*cos(e->angle * (M_PI / 180))) + 0.5;
	e->numpix = (int)x + (int)y * 100 + (int)z;
	ft_light_pixel(e);
}

int		ft_key_funct(int keycode, t_add *e)
{
	printf("keycode event %d\n", keycode);
	if (keycode == 123)
	{
		e->angle += 10;
		ft_matrice(10, 10, 10, e);
	}
	if (keycode == 124)
	{
		e->angle -= 10;
		ft_matrice(10, 10, 10, e);
	}
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

int main(void)
{
	ft_draw_pix();
	return (0);
}
