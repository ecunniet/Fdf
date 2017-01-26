/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:16:57 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/26 19:57:37 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx/mlx.h"

int					ft_verif_x(int xmax_new, int xmax_old);
void				ft_error(int i, char *str);

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	int				R;
	int				G;
	int				B;
}					t_point;

typedef	struct		s_pixel
{
	double			x;
	double			y;
	double 			z;
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
	double			zoom;
	double			angle_y;
	double			angle_x;
	double			angle_z;
	int				b_x;
	int				b_y;
	int				b_z;
}					t_env;

#endif
