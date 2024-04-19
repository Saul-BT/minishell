/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:14 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		num_chars;
	char	*scpy;

	i = 0;
	num_chars = ft_strlen(s);
	scpy = (char *)malloc((num_chars + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	while (i < num_chars)
	{
		scpy[i] = s[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}
