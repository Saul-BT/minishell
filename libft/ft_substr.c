/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:19 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	char	*result;

	if (!s || start < 0)
		return (NULL);
	s_len = ft_strlen(s);
	sub_len = ft_strlen(&s[start]);
	if (s_len < start)
		sub_len = 0;
	else if (sub_len > len)
		sub_len = len;
	result = malloc((sub_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[sub_len] = '\0';
	while (sub_len--)
		result[sub_len] = s[start + sub_len];
	return (result);
}
