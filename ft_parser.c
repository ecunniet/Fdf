/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:48:49 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/06 15:48:54 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*ft_strmydup(char const *s1, char c)
{
	char	*s2;
	size_t	i;

	i = 0;
	while (s1[i] != c && s1[i] != '\0')
		i++;
	if (!(s2 = (char*)malloc(sizeof(char) * (i + 1))))
	{
		write(1, "pb malloc.\n", 9);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (s1[i] != c && s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static char	*ft_mysplit(char *s, char c, int nbword)
{
	int		z;
	int		j;

	z = 0;
	j = 0;
	while (j < nbword && s[z] != '\0')
	{
		if (s[z] != c && (s[z + 1] == c || s[z + 1] == '\0'))
			j++;
		z++;
	}
	z--;
	while (s[z] != c && z >= 0)
		if (--z < 0)
			break ;
	z++;
	return (ft_strmydup(s + z, c));
}

static void	ft_parser(t_env *list, int i, int x, int y)
{
	if (!(list->p = (t_point*)malloc(sizeof(t_point)
	* (list->ymax * list->xmax))))
		return ;
	if (!(list->h = (t_pixel*)malloc(sizeof(t_pixel)
	* (list->ymax * list->xmax))))
		return ;
	if (!(list->tmp = (t_pixel*)malloc(sizeof(t_pixel)
	* (list->ymax * list->xmax))))
		return ;
	while (get_next_line(list->fd, &list->line))
	{
		x = 0;
		while (x < list->xmax)
		{
			list->str = ft_mysplit(list->line, ' ', x + 1);
			(list->p + i)->z = y;
			(list->p + i)->x = x;
			(list->p + i)->y = -ft_atoi(list->str);
			free(list->str);
			x++;
			i++;
		}
		free(list->line);
		y++;
	}
}

static int	ft_count_x(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (s == NULL)
		ft_error(2, 0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

void		ft_get_pix(char *filename, t_env *list)
{
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_count_x(list->line, ' '), list->xmax);
			free(list->line);
			list->ymax++;
		}
		if (close(list->fd) == 0)
		{
			if ((list->fd = open(filename, O_RDONLY)))
			{
				ft_parser(list, 0, 0, 0);
				if (close(list->fd) == -1)
					ft_error(4, 0);
			}
		}
		else
			ft_error(4, 0);
	}
	else
		ft_error(1, filename);
}
