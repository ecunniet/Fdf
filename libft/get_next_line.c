/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:58:23 by ecunniet          #+#    #+#             */
/*   Updated: 2016/12/12 19:18:24 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static	int		ft_read_file(char **line, char (*mem)[], int fd)
{
	char	tmp[BUFF_SIZE + 1];
	char	*ptr;
	int		ret;

	while ((ret = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[ret] = 0;
		if ((ptr = ft_strchr(tmp, '\n')))
		{
			*ptr = 0;
			ptr++;
			ft_strcpy((char*)mem, ptr);
			*line = (*line == NULL) ? ft_strdup(tmp)
				: ft_strjoin_free(*line, tmp, 1);
			return (1);
		}
		else
			*line = (*line == NULL) ? ft_strdup(tmp)
				: ft_strjoin_free(*line, tmp, 1);
	}
	if (ret == -1)
		return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		mem[BUFF_SIZE + 1] = "";
	int				i;
	char			*ptr;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (ft_strlen(mem) > 0)
	{
		if ((ptr = ft_strchr(mem, '\n')))
		{
			*ptr = 0;
			ptr++;
			*line = ft_strdup(mem);
			ft_strcpy(mem, ptr);
			return (1);
		}
		else
		{
			*line = ft_strdup(mem);
			*mem = 0;
		}
	}
	i = ft_read_file(&(*line), &mem, fd);
	return (i == 0 && *line != NULL) ? 1 : i;
}
