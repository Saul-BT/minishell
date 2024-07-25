/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 09:53:05 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_diff(const unsigned char c1, const unsigned char c2)
{
	if (c1 < c2)
		return (-1);
	else if (c1 > c2)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	diff = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != '\0' && s2 && *s2 != '\0')
	{
		diff = get_diff(s1[i], s2[i]);
		if (diff != 0)
			return (diff);
		i++;
	}
	if (i < n)
		return (get_diff(s1[i], s2[i]));
	else
		return (0);
}
