/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:00:46 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/15 16:34:50 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_pipe(char c)
{
	return (c == '|');
}

static int	count_pipes(const char *str)
{
	int		count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!is_quoted(*str) && is_pipe(*str))
			count++;
		str++;
	}
	return (count);
}

static void	get_piped_cmds(const char *str, char ***cmds, int cmd_count)
{
	size_t	i;
	int		j;
	bool	ispipe;
	size_t	wb_index;
	size_t	cmd_start_index;

	i = 0;
	j = 0;
	ispipe = false;
	wb_index = 0;
	cmd_start_index = 0;
	while (is_space(str[i]))
		i++;
	while (i <= ft_strlen(str))
	{
		ispipe = is_pipe(str[i]);
		if (str[i] && is_quoted(str[i]))
			ispipe = false;
		if (i > 0 && is_word_boundary(str[i - 1], str[i]))
			wb_index = i;
		if (j > 0 && cmd_start_index == 0 && !ispipe && is_word_boundary(str[i],
				str[i - 1]))
			cmd_start_index = i;
		if (ispipe || !str[i])
		{
			if (j == cmd_count - 1)
				(*cmds)[j++] = ft_substr(str, cmd_start_index, ft_strlen(str)
						- cmd_start_index);
			else
				(*cmds)[j++] = ft_substr(str, cmd_start_index, wb_index
						- cmd_start_index);
			cmd_start_index = 0;
		}
		i++;
	}
}

char	**pipe_split(const char *str, int *cmd_count)
{
	char **result;

	*cmd_count = count_pipes(str) + 1;
	if (is_quoted('?'))
		return (NULL);
	result = ft_calloc(*cmd_count, sizeof(char *));
	if (*cmd_count == 1)
	{
		result[0] = ft_strdup(str);
		return (result);
	}
	get_piped_cmds(str, &result, *cmd_count);
	return (result);
}