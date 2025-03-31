/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:59:56 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/31 15:03:54 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_token	*handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	t_parsed_token	*result;
	t_parsed_token	*other;
	int				mode;
	int				fd;

	result = malloc(sizeof(t_parsed_token)); // TODO: Add null-check
	result->skip = 0;
	result->parsed = NULL;
	mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (token[1] == '>')
	{
		mode = O_RDWR | O_CREAT | O_APPEND;
		result->skip++;
		token++;
	}
	while (ft_isspace(*++token))
		result->skip++;
	if (!*token || (*token && ft_strchr("<>", *token) && g_exit_num != 2))
	{
		printf("pipex: syntax error near unexpected token `>'\n");
		g_exit_num = 2;
		return (result);
	}
	if (*token)
	{
		if (ft_strchr("'\"", token[0]))
		{
			other = handle_quote(token + 1, token[0], cfg);
		}
		else
		{
			other = handle_other(token, cfg);
		}
		result->skip += other->skip + 1;
		fd = open(other->parsed, mode, 0644);
		free(other->parsed);
		free(other);
		if (fd == -1)
			return (result);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	return (result);
}
