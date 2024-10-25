/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:47:20 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 16:52:19 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printmat(char **m)
{
	int	i;

	while (m[i])
	{
		printf("%s\n", m[i]);
		i++;
	}
}

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
