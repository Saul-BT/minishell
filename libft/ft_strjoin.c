/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 15:54:34 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i1;
	int		i2;
	char	*result;

	i1 = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i1] != '\0')
	{
		result[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != '\0')
	{
		result[i1 + i2] = s2[i2];
		i2++;
	}
	result[i1 + i2] = '\0';
	return (result);
}
