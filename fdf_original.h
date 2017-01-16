/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:16:57 by ecunniet          #+#    #+#             */
/*   Updated: 2017/01/16 22:03:58 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx/mlx.h"

int					ft_verif_x(char **point, int xmax);
void				ft_error(int i, char *str);

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				R;
	int				G;
	int				B;
}					t_point;

typedef	struct		s_pixel
{
	int				x;
	int				y;
	int 			z;
}					t_pixel;

typedef struct		s_env
{
	int				fd;
	void			*mlx;
	void			*win;
	char			*line;
	t_point			*p;
	t_pixel			*h;
	int				xmax;
	int				ymax;
}					t_env;

typedef struct		s_img
{
	void			*img_ptr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	char			*adi;
}					t_img;

#endif
