/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:10 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n)
	{
		c1 = ((unsigned char *)s1)[i];
		c2 = ((unsigned char *)s2)[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}
