/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:28:20 by ecunniet          #+#    #+#             */
/*   Updated: 2016/11/22 14:20:35 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next != NULL)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = tmp;
}
