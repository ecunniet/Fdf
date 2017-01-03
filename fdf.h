/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 18:16:57 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/19 22:11:47 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx/mlx.h"

int	ft_verif_x(char **point, int xmax);
void	ft_error(int i, char *str);

typedef struct		s_env
{
	void	*mlx;
	void	*win;
	char	*line;
	int		*x;
	int		*y;
	int		*z;
	int		xmax;
	int		ymax;
}					t_env;

#endif
