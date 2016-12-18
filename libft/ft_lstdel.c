/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:38:31 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/17 15:50:45 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	tmp = *alst;
	while ((*alst)->next != NULL)
	{
		*alst = tmp;
		del((*alst)->content, (*alst)->content_size);
		tmp = (*alst)->next;
		free(*alst);
	}
	*alst = NULL;
}
