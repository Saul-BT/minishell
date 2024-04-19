/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:15:03 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX_SIZE 18446744073709551615UL

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*room;

	if (nmemb >= MAX_SIZE || size >= MAX_SIZE)
		return (NULL);
	room = (void *)malloc(nmemb * size);
	if (!room)
		return (NULL);
	ft_bzero(room, nmemb * size);
	return (room);
}
