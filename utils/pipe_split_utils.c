/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:43:44 by mmartine          #+#    #+#             */
/*   Updated: 2025/02/12 22:44:23 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_word_boundary(char a, char b)
{
	return (!ft_isspace(a) && ft_isspace(b));
}

bool	is_symbol(char c, char symbol)
{
	return (c == symbol);
}

bool	is_quoted(char c)
{
	static t_quoted	quote = NOPE;

	if (quote != NOPE)
	{
		if (is_symbol(c, '\'') && quote == SINGLE_QUOTE)
			quote = NOPE;
		else if (is_symbol(c, '"') && quote == DOUBLE_QUOTE)
			quote = NOPE;
		return (true);
	}
	if (is_symbol(c, '\''))
		quote = SINGLE_QUOTE;
	else if (is_symbol(c, '"'))
		quote = DOUBLE_QUOTE;
	return (false);
}

void	close_quote(void)
{
	is_quoted('"');
	if (is_quoted('?'))
		is_quoted('\'');
}

int	count_pipes(const char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (!is_quoted(str[i]) && is_symbol(str[i], '|'))
			count++;
		i++;
	}
	return (count);
}