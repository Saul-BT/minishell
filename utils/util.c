/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:47:20 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/15 10:28:39 by sblanco-         ###   ########.fr       */
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
