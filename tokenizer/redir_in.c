/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:52:32 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/31 18:09:43 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_fd_in_redir(t_parsed_token *result, t_shell *cfg, char *token)
{
	int				fd;
	t_parsed_token	*other;

	if (ft_strchr("'\"", token[0]))
		other = handle_quote(token + 1, token[0], cfg);
	else
		other = handle_other(token, cfg);
	result->skip += other->skip + 1;
	fd = open(other->parsed, O_RDONLY);
	free(other->parsed);
	free(other);
	// if (fd == -1)
	// TODO: Handle error
	return (fd);
}

t_parsed_token	*handle_in_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	t_parsed_token	*result;
	int				fd;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	result->parsed = NULL;
	while (ft_isspace(*++token))
		result->skip++;
	if (!*token || (*token && *token == '>' && g_exit_num != 2))
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		g_exit_num = 2;
		return (result);
	}
	if (*token)
	{
		fd = get_fd_in_redir(result, cfg, token);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_in = fd;
	}
	return (result);
}
