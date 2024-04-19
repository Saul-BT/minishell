/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:44 by sblanco-          #+#    #+#             */
/*   Updated: 2023/05/22 22:09:56 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	index_of(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
		return (-1);
	return (i);
}

static int	count_chunks(char const *s, char c)
{
	int	num_chunks;

	num_chunks = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			num_chunks++;
			while (*s && *s != c)
				s++;
		}
		else
			while (*s && *s == c)
				s++;
	}
	return (num_chunks);
}

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

static int	set_words(char const *s, char c, int chunk_count, char **dst_strs)
{
	int	i;
	int	cur_c_index;

	i = 0;
	while (*s && i < chunk_count)
	{
		if (*s != c)
		{
			cur_c_index = index_of(s, c);
			if (cur_c_index == -1)
				cur_c_index = ft_strlen(s);
			dst_strs[i] = ft_substr(s, 0, cur_c_index);
			if (!dst_strs[i++])
			{
				free_strs(dst_strs);
				return (0);
			}
			s += cur_c_index;
		}
		while (*s && *s == c)
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		chunk_count;

	if (!s)
		return (NULL);
	chunk_count = count_chunks(s, c);
	strs = ft_calloc(sizeof(char *), chunk_count + 1);
	if (!strs)
		return (NULL);
	if (!set_words(s, c, chunk_count, strs))
		return (NULL);
	return (strs);
}
