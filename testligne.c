#include "minilibx/mlx.h"

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
	x = xi;
	y = yi;
	dx = xf - xi;
	dy = yf - yi;
	*(e->adi + (x + y * 100) * 4) = 255;
	*(e->adi + 1 + (x + y * 100) * 4) = 255;
	*(e->adi + 2 + (x + y * 100) * 4) = 255;
	cumul = dx / 2;
	while (x <= xf)
	{
		x++;
		cumul += dy;
		if (cumul >= dx)
		{
			cumul -= dx;
			y++;
		}
		*(e->adi + (x  + y * 100) * 4) = 255;
		*(e->adi + 1 + (x + y * 100) * 4) = 255;
		*(e->adi + 2 + (x + y * 100) * 4) = 255;
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
