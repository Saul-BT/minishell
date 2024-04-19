/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2023/04/10 20:25:15 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	clean(t_node *node, void (*del)(void *))
{
	if (del)
		(*del)(node->content);
	free(node);
}

void	ft_lstclear(t_node **lst, void (*del)(void *))
{
	t_node	*node_nd;

	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		node_nd = (*lst)->next;
		clean((*lst), del);
		(*lst) = node_nd;
	}
}
