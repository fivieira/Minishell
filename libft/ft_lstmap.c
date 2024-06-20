/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:41:09 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/17 07:55:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*node;

	if (!lst)
		return (NULL);
	output = ft_lstnew(f(lst->content));
	if (output == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		node = ft_lstnew(f(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&output, del);
			return (NULL);
		}
		ft_lstadd_back(&output, node);
	}
	return (output);
}
