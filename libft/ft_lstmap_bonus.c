/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2023/03/14 23:26:17 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstmap(t_node *lst, void *(*f)(void *), void (*del)(void *))
{
	t_node			*head_lst_transformed;
	t_node			*lst_transformed;

	if (!lst || !f)
		return (NULL);
	lst_transformed = ft_lstnew(f(lst->content));
	head_lst_transformed = lst_transformed;
	if (!head_lst_transformed)
	{
		free(lst_transformed);
		return (NULL);
	}
	while (lst->next)
	{
		lst = lst->next;
		(lst_transformed)->next = ft_lstnew(f(lst->content));
		lst_transformed = (lst_transformed)->next;
		if (!lst_transformed)
		{
			ft_lstclear(&head_lst_transformed, del);
			return (NULL);
		}
	}
	return (head_lst_transformed);
}
