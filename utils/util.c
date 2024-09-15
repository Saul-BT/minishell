/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:47:20 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/15 16:54:22 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_cmds(char ***cmds, int cmd_count)
{
	int	i;

	i = 0;
	while (cmds && i < cmd_count)
	{
		free_strs(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

bool	has_char(const char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	starts_with(const char *str, const char *prefix)
{
	while (str && *prefix && *str)
	{
		if (*prefix != *str)
			return (false);
		prefix++;
		str++;
	}
	return (true);
}

bool	is_space(char c)
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

bool	is_word_boundary(char a, char b)
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