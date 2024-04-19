/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:18 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_match(const char *big, const char *little)
{
	unsigned long	little_len;
	unsigned long	i;

	i = 0;
	little_len = ft_strlen(little);
	while ((big[i] && little[i]) && big[i] == little[i])
		i++;
	return (little_len == i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	big_len;
	size_t	little_len;

	i = 0;
	big_len = ft_strlen(big);
	little_len = ft_strlen(little);
	if (little_len > big_len)
		return (NULL);
	if (!little_len)
		return ((char *)big);
	while (i < len && big[i])
	{
		if ((i + little_len) > len)
			break ;
		if (is_match(&big[i], little))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
