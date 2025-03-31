/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:59:56 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/31 20:09:56 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_parsed_token	*init_handle_out(int *mode, char **token)
{
	t_parsed_token	*result;

	result = malloc(sizeof(t_parsed_token));
	if (!result)
		return (NULL);
	result->skip = 0;
	result->parsed = NULL;
	*mode = O_WRONLY | O_CREAT | O_TRUNC;
	if ((*token)[1] == '>')
	{
		*mode = O_RDWR | O_CREAT | O_APPEND;
		result->skip++;
		(*token)++;
	}
	return (result);
}

static int	get_fd_in_redir_out(t_shell *cfg, char *token,
	t_parsed_token *result, int mode)
{
	int				fd;
	t_parsed_token	*other;

	if (ft_strchr("'\"", token[0]))
		other = handle_quote(token + 1, token[0], cfg);
	else
		other = handle_other(token, cfg);
	if (!accesible_file(other->parsed, mode))
	{
		result->skip += ft_strlen(token) + 1;
		free(other->parsed);
		free(other);
		return (STDOUT_FILENO);
	}
	result->skip += other->skip + 1;
	fd = open(other->parsed, mode, 0644);
	free(other->parsed);
	free(other);
	return (fd);
}

t_parsed_token	*handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	t_parsed_token	*result;
	int				mode;
	int				fd;

	result = init_handle_out(&mode, &token);
	while (ft_isspace(*++token))
		result->skip++;
	if (!*token || (*token && ft_strchr("<>", *token)))
	{
		while(*token && ft_strchr("<>", *token++))
			result->skip++;
		if (mode & O_APPEND)
			printf("minishell: syntax error near unexpected token `>>'\n");
		else
			printf("minishell: syntax error near unexpected token `>'\n");
		g_exit_num = 2;
		result->skip += ft_strlen(token) + 1;
		return (result);
	}
	if (*token)
	{
		fd = get_fd_in_redir_out(cfg, token, result, mode);
		if (fd == -1)
			return (result);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	return (result);
}

// t_parsed_token	*handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg)
// {
// 	t_parsed_token	*result;
// 	t_parsed_token	*other;
// 	int				mode;
// 	int				fd;

// 	result = malloc(sizeof(t_parsed_token));
// 	if (!result)
// 		return (NULL);
// 	result->skip = 0;
// 	result->parsed = NULL;
// 	mode = O_WRONLY | O_CREAT | O_TRUNC;
// 	if (token[1] == '>')
// 	{
// 		mode = O_RDWR | O_CREAT | O_APPEND;
// 		result->skip++;
// 		token++;
// 	}
// 	while (ft_isspace(*++token))
// 		result->skip++;
// 	if (!*token || (*token && ft_strchr("<>", *token) && g_exit_num != 2))
// 	{
// 		printf("pipex: syntax error near unexpected token `>'\n");
// 		g_exit_num = 2;
// 		return (result);
// 	}
// 	if (*token)
// 	{
// 		if (ft_strchr("'\"", token[0]))
// 			other = handle_quote(token + 1, token[0], cfg);
// 		else
// 			other = handle_other(token, cfg);
// 		result->skip += other->skip + 1;
// 		fd = open(other->parsed, mode, 0644);
// 		free(other->parsed);
// 		free(other);
// 		if (fd == -1)
// 			return (result);
// 		if (cmd->fd_out != 1)
// 			close(cmd->fd_out);
// 		cmd->fd_out = fd;
// 	}
// 	return (result);
// }
