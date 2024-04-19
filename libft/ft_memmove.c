/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:11 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srcc;
	unsigned char	*destc;

	i = -1;
	srcc = (unsigned char *)src;
	destc = (unsigned char *)dest;
	if (src == dest)
		return (dest);
	else if (src < dest)
		while (n--)
			destc[n] = srcc[n];
	else
		while (++i < n)
			destc[i] = srcc[i];
	return (dest);
}
