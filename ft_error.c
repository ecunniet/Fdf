/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:48:25 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/06 15:48:29 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_verif_x(int xmax_new, int xmax_old)
{
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (xmax_old == -1 && xmax_new == 0)
		ft_error(2, 0);
	else if (xmax_old == -1 && xmax_new > 0)
		return (xmax_new);
	else if (xmax_new != xmax_old)
		ft_error(3, 0);
	return (xmax_new);
}

void		ft_error(int i, char *str)
{
	if (i == 0)
		ft_putstr("Usage: ./fdf <filename> [ case_size z_size ]\n");
	if (i == 1)
	{
		ft_putstr("No file");
		ft_putstr(str);
		ft_putchar('\n');
	}
	if (i == 2)
		ft_putstr("No data found.\n");
	if (i == 3)
		ft_putstr("Found wrong line length. Exiting.\n");
	if (i == 4)
		ft_putstr("Fail to close file\n");
	exit(EXIT_FAILURE);
}

void		ft_free_struct(t_env *list)
{
	free(list->p);
	free(list->tmp);
	free(list->h);
	exit(EXIT_SUCCESS);
}

static void	ft_initrainbow(t_env *list)
{
	list->rainbow = 0;
	list->b_x = 0;
	list->b_y = 0;
	list->b_z = 0;
	*(list->r) = 0xf40000;
	*(list->r + 1) = 0xffa500;
	*(list->r + 2) = 0xf4f400;
	*(list->r + 3) = 0x00f400;
	*(list->r + 4) = 0x0028f4;
	*(list->r + 5) = 0xa300f4;
	list->nblr = (int)(list->ymax) / 6;
	list->modr = (int)(list->ymax) % 6;
}

int			ft_draw_pix(t_env *list)
{
	list->zoom = 1;
	list->angle_x = 15;
	list->angle_y = 25;
	list->angle_z = 0;
	list->center_x = -1;
	list->center_y = -1;
	ft_initrainbow(list);
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, WIDTH, HEIGHT, "mlx_42");
	list->img_ptr = mlx_new_image(list->mlx, WIDTH, HEIGHT);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_key_hook(list->win, ft_key_funct, list);
	mlx_mouse_hook(list->win, ft_mouse_funct, list);
	mlx_loop_hook(list->mlx, ft_fill_image, list);
	mlx_loop(list->mlx);
	return (0);
}
