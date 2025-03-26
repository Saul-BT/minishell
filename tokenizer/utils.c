/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:00:43 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/26 14:50:06 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*file_name_non_quoted(char *name)
{
	char	*non_q;

	if (name[0] == '"')
	{
		free(name);
		non_q = ft_strtrim(name, "\"");
	}
	else if (name[0] == '\'')
	{
		free(name);	
		non_q = ft_strtrim(name, "'");
	}
	else
		return (name);
	return (non_q);
}

t_cmd	*init_tokenizer(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	return (cmd);
}