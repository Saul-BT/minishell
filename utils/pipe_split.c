/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:00:46 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/17 19:01:23 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	realpipe(const char *str, size_t i)
{
	bool	ispipe;

	ispipe = false;
	ispipe = is_symbol(str[(i)], '|');
	if (str[(i)] && is_quoted(str[(i)]))
		ispipe = false;
	return (ispipe);
}

static size_t	st_ind_value(int j, bool ispipe, const char *str, size_t i)
{
	if (j > 0 && !ispipe && is_word_boundary(str[(i)], str[(i) - 1]))
		return (i);
	return (0);
}

static void	get_piped_cmds(const char *str, char ***cmds,
	int cmd_count, size_t *i)
{
	int		j;
	bool	ispipe;
	size_t	wb_index;
	size_t	st_ind;

	j = 0;
	wb_index = 0;
	st_ind = 0;
	while (*i <= ft_strlen(str))
	{
		ispipe = realpipe(str, *i);
		if ((*i > 0 && is_word_boundary(str[(*i) - 1], str[(*i)])))
			wb_index = *i;
		if (st_ind == 0)
			st_ind = st_ind_value(j, ispipe, str, *i);
		if (ispipe || !str[*i])
		{
			if (j == cmd_count - 1)
				(*cmds)[j++] = ft_substr(str, st_ind, ft_strlen(str) - st_ind);
			else
				(*cmds)[j++] = ft_substr(str, st_ind, wb_index - st_ind);
			st_ind = 0;
		}
		(*i)++;
	}
}

char	**pipe_split(const char *str, int *cmd_count)
{
	char	**result;
	size_t	i;

	i = 0;
	*cmd_count = count_pipes(str) + 1;
	if (is_quoted('?'))
		return (NULL);
	result = ft_calloc(*cmd_count, sizeof(char *));
	if (*cmd_count == 1)
	{
		result[0] = ft_strdup(str);
		return (result);
	}
	while (ft_isspace(str[i]))
		i++;
	get_piped_cmds(str, &result, *cmd_count, &i);
	return (result);
}
