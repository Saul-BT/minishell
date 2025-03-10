/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:47:20 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/10 19:56:30 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printmat(char **m)
{
	int	i;

	i = 0;
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

void	free_args(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	ft_lstclear(&(cmd->args), free);
}

void	free_cmds(t_node *cmds)
{
	ft_lstiter(cmds, (void (*)(void *))free_args);
	ft_lstclear(&cmds, free);
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
