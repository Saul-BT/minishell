/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hered.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:40 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/03 21:48:17 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_loop(t_shell *cfg, char *delimiter, t_cmd *cmd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	g_exit_num = 0;
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, pipe_fd[0]);
		close(cmd->fd_out);
	}
	while (true)
	{
		sig_manage(cfg, 2);
		signal(SIGQUIT, SIG_IGN);
		line = readline("heredoc> ");
		sig_manage(cfg, 1);
		if (g_exit_num == 130 || !line || ft_strcmp(line, delimiter) == 0)
		{
			cfg->exit_code = g_exit_num;
			free(line);
			break ;
		}
		write_in_heredoc(line, cfg, pipe_fd);
	}
	return (manage_heredoc_pipes(pipe_fd, cmd), 1);
}

static t_parsed_token	*init_heredoc(size_t *skip, char **token)
{
	t_parsed_token	*result;

	*skip = 1;
	result = malloc(sizeof(t_parsed_token));
	if (!result)
		return (NULL);
	result->skip = 0;
	result->parsed = NULL;
	*token += 2;
	while (ft_isspace(**token))
	{
		(*token)++;
		(*skip)++;
	}
	return (result);
}

static char	*get_heredoc_delimiter(char *token, size_t *next_symbol_idx)
{
	*next_symbol_idx = ft_index_of_symbol(token);
	if (*next_symbol_idx == (size_t)-1)
		*next_symbol_idx = ft_strlen(token);
	return (ft_substr(token, 0, *next_symbol_idx));
}

t_parsed_token	*handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			skip;
	size_t			next_symbol_idx;
	t_parsed_token	*result;
	char			*delimiter;

	result = init_heredoc(&skip, &token);
	if (!result)
		return (NULL);
	if (!*token || (*token && strchr("<>", *token)))
	{
		while (*token && ft_strchr("<>", *token++))
			result->skip++;
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (cfg->exit_code = 2, result->skip += ft_strlen(token) + 2, result);
	}
	if (*token && g_exit_num != 2)
	{
		delimiter = get_heredoc_delimiter(token, &next_symbol_idx);
		if (!heredoc_loop(cfg, delimiter, cmd))
			return (NULL);
		skip += next_symbol_idx;
		free(delimiter);
	}
	result->skip = skip;
	return (result);
}
