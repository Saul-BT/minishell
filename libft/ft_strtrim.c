/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2022/08/12 10:16:19 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_end_len(char const *s, char const *set, int s_len)
{
	int		end_len;

	end_len = 0;
	while (ft_strchr(set, s[(s_len - 1) - end_len]))
		end_len++;
	return (end_len);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		i;
	int		result_len;
	char	*result;

	if (!s || !set)
		return ((char *)s);
	while (*s && ft_strchr(set, *s))
		s++;
	i = 0;
	result_len = ft_strlen(s);
	if (result_len > 0)
		result_len = result_len - get_end_len(s, set, result_len);
	result = malloc((result_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < result_len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
