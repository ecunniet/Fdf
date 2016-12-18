/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:57:12 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/16 17:28:14 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (*alst != NULL)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
	}
	*alst = NULL;
}
