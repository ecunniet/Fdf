/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:11:38 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/13 17:08:34 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_location(char **str, int y)
{

}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**point;
	int		y;

	y = 0;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)))
		{
			while (get_next_line(fd, &str))
			{
				point = ft_strsplit(str, ' ');
				ft_location(point, y);
				y++;
			}
		}
		else
			return(ft_erreur(1, argv[1]));
	}
	else
		return (ft_error(0, 0));
	return (0);
}
