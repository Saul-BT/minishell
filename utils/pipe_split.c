/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:00:46 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 13:20:59 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || (c == ' '));
}

static inline bool	is_pipe(char c)
{
	return (c == '|');
}

static inline bool	is_word_boundary(char a, char b)
{
	return (a != ' ' && b == ' ');
}

static size_t	count_pipes(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (is_pipe(str[i]))
			count++;
		i++;
	}
	return (count);
}

static void	get_piped_cmds(const char *str, char ***cmds)
{
	size_t	i;
	size_t	j;
	size_t	wb_index;
	size_t	cmd_start_index;

	i = 0;
	j = 0;
	wb_index = 0;
	cmd_start_index = 0;
	while (is_space(str[i]))
		i++;
	while (i <= ft_strlen(str))
	{
		if (i > 0 && is_word_boundary(str[i - 1], str[i]))
			wb_index = i;
		if (i > 0 && cmd_start_index == 0 && !is_pipe(str[i])
			&& is_word_boundary(str[i], str[i - 1]))
			cmd_start_index = i;
		if (str[i] == '\0' || is_pipe(str[i]))
		{
			*cmds[j++] = ft_substr(str, cmd_start_index, wb_index
					- cmd_start_index);
			cmd_start_index = 0;
		}
	}
}

char	**pipe_split(const char *str, size_t *pipe_count)
{
	char	**result;

	*pipe_count = count_pipes(str);
	result = ft_calloc(*pipe_count + 1, sizeof(char *));
	if (*pipe_count == 0)
	{
		result[0] = ft_strdup(str);
		return (result);
	}
	get_piped_cmds(str, &result);
	return (result);
}
