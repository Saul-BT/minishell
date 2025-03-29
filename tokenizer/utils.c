/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:00:43 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/29 20:59:10 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_index_of_symbol(char *str)
{
	static char	*symbols = " <>;'\"";
	size_t		i;

	i = 0;
	if (!*str)
		return ((size_t)-1);
	while (str[i])
	{
		if (ft_strchr(symbols, str[i]))
			return (i);
		i++;
	}
	return ((size_t)-1);
}

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
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	return (cmd);
}