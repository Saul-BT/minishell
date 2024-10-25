/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/10 18:45:40 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dest_len > dstsize)
		return (src_len + dstsize);
	if (dstsize == 0)
		return (src_len);
	while (src[i] && (i + dest_len + 1) < dstsize)
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	if (dst)
		dst[i + dest_len] = '\0';
	if (dest_len > dstsize)
		dest_len = dstsize;
	return (src_len + dest_len);
}
