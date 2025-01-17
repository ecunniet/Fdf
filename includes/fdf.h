/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:16:57 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/05 22:24:00 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# define WIDTH 1000
# define HEIGHT 600

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef	struct		s_pixel
{
	double			x;
	double			y;
	double			z;
}					t_pixel;

typedef struct		s_env
{
	int				fd;
	void			*mlx;
	void			*win;
	char			*line;
	t_point			*p;
	t_pixel			*tmp;
	t_pixel			*h;
	double			xmax;
	double			ymax;
	void			*img_ptr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	char			*adi;
	int				color;
	double			zoom;
	int				center_x;
	int				center_y;
	double			angle_y;
	double			angle_x;
	double			angle_z;
	int				b_x;
	int				b_y;
	int				b_z;
	char			*str;
	int				rainbow;
	int				nblr;
	int				modr;
	int				r[6];
}					t_env;

typedef	struct		s_line
{
	int				dx;
	int				dy;
	int				err;
	int				xi;
	int				yi;
	int				xf;
	int				yf;
	int				xinc;
	int				yinc;
	int				i;
}					t_line;

void				ft_free_struct(t_env *list);
int					ft_key_funct(int keycode, t_env *list);
int					ft_mouse_funct(int button, int x, int y, t_env *list);
void				ft_call_bresenham(t_env *list, int i, int color, int v);
int					ft_fill_image(t_env *list);
int					ft_draw_pix(t_env *list);
void				ft_get_pix(char *filename, t_env *list);
int					ft_verif_x(int xmax_new, int xmax_old);
void				ft_error(int i, char *str);

#endif
