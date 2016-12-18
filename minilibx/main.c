/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 19:29:10 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/19 00:20:03 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <stdio.h>

typedef struct		s_mlx
{
	void	*mlx;
	void	*win;
}					t_mlx;

typedef	struct		s_address
{
	int					x;
	int					y;
	int					z;
	struct s_address	*next;
}					t_adress;

//compilation: cc -o mlx main.c -lmlx -framework OpenGL -framework AppKit

int		my_key_funct(int keycode, t_mix *e/*structure avec plusieurs param?*/)
{
	printf("keycode event %d\n", keycode);
	mlx_pixel_put(e->mlx, e->win, 300, 300, 0xFF00FF);
	return (0);
}

int	main(void)
{
	t_mlx	e;
	int		x;
	int		y;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 400, 400, "mlx_42");
	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 150)
		{
			mlx_pixel_put(e.mlx, e.win, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_key_hook(e.win, my_key_funct, &e);
	mlx_loop(e.mlx);
}

//////////////////////////////////////////////////////

t_address	*ft_location(char **point, int y)
{	
	t_address	*tmp;
	t_address	*pix;
	int			x;

	x = 0;
	while (point[x])
	{
		pix->x = x;
		pix->y = y;
		pix->z = ft_atoi(point[x]);
		if ()
		*pix = pix->next;
		x++;
	}
}

int		ft_get_pix(char *filename)
{
	int			fd;
	char		*line;
	char		**point;
	int			y;
	int			xmax;
	t_address	*list;

	xmax = -1;
	y = 0;
	if ((fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(fd, &line))
		{
			y++;
			point = ft_strsplit(line, ' ');
			xmax = ft_verif_x(point, xmax);
			list = (y == 0) ? ft_location(point, y)
			: ft_lstaddend(&list, ft_location(point, y));
		}
	}
	else
		ft_erreur(1, argv[1]);
	return(0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		ft_get_pix(argv[1]);
	else
		ft_error(0, 0);
	return (0);
}
