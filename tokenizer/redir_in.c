/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:52:32 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/03 20:27:55 by sblanco-         ###   ########.fr       */
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
	if (!accesible_file(other->parsed, O_RDONLY))
	{
		result->skip = ft_strlen(token) + 1;
		free(other->parsed);
		free(other);
		fd = open("/dev/null", O_RDONLY);
		return (fd);
	}
	fd = open(other->parsed, O_RDONLY);
	free(other->parsed);
	free(other);
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
	if (!*token || (*token && *token == '>'))
	{
		while (*token && *token++ == '>')
			result->skip++;
		printf("minishell: syntax error near unexpected token `<'\n");
		g_exit_num = 2;
		result->skip += ft_strlen(token) + 1;
		return (result);
	}
	if (*token)
	{
		fd = get_fd_in_redir(result, cfg, token);
		cmd->fd_in = fd;
	}
	return (result);
}
