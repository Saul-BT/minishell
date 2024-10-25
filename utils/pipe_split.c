/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:00:46 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/09 19:44:20 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || (c == ' '));
}

static inline bool	is_single_quote(char c)
{
	return (c == '\'');
}

static inline bool	is_double_quote(char c)
{
	return (c == '"');
}

static bool	is_pipe(char c)
{
	return (c == '|');
}

static inline bool	is_word_boundary(char a, char b)
{
	return (!is_space(a) && is_space(b));
}

bool	is_quoted(char c)
{
	static t_quoted	quote = NOPE;

	if (quote != NOPE)
	{
		if (is_single_quote(c) && quote == SINGLE_QUOTE)
			quote = NOPE;
		else if (is_double_quote(c) && quote == DOUBLE_QUOTE)
			quote = NOPE;
		return (true);
	}
	if (is_single_quote(c))
		quote = SINGLE_QUOTE;
	else if (is_double_quote(c))
		quote = DOUBLE_QUOTE;
	return (false);
}

void	close_quote()
{
	is_quoted('"');
	if (is_quoted('?'))
		is_quoted('\'');
}

static int	count_pipes(const char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (!is_quoted(str[i]) && is_pipe(str[i]))
			count++;
		i++;
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