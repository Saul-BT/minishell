/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:10 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sc;

	if (!n)
		return (NULL);
	i = 0;
	sc = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char)c == sc[i])
			return ((void *)(&s[i]));
		i++;
	}
	if (c == '\0')
		return ((void *)(&s[i]));
	return (NULL);
}
