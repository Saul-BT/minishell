/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hered.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:40 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/31 14:56:41 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_heredoc_pipes(int pipe_fd[2], t_cmd *cmd)
{
	close(pipe_fd[1]);
	if (cmd->fd_in > 1)
		close(cmd->fd_in);
	cmd->fd_in = pipe_fd[0];
}

int	heredoc_loop(t_shell *cfg, char *delimiter, t_cmd *cmd)
{
	char	*line;
	char	*aux;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0); // TODO: Handle error
	g_exit_num = 0;
	while (1)
	{
		sig_manage(cfg, 2);
		signal(SIGQUIT, SIG_IGN);
		line = readline("heredoc> ");
		sig_manage(cfg, 1);
		// FIXME: !line???
		if (g_exit_num == 130 || !line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		aux = line;
		line = expand_super(aux, cfg);
		free(aux);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	manage_heredoc_pipes(pipe_fd, cmd);
	return (1);
}

t_parsed_token	*init_heredoc(size_t *skip, char **token)
{
	t_parsed_token	*result;

	*skip = 1; // Skip '<<'
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

char	*get_heredoc_delimiter(char *token, size_t *next_symbol_idx)
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
	if (!*token || (*token && strchr("<>", *token) && g_exit_num != 2))
	{
		printf("pipex: syntax error near unexpected token `<'\n");
		g_exit_num = 2;
		return (result);
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

// t_parsed_token	*handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg)
// {
// 	size_t			skip;
// 	size_t			next_symbol_idx;
// 	t_parsed_token	*result;
// 	// char			*delimiter;
// 	char			*line;
// 	// int				pipe_fd[2];

// 	skip = 1;                                // Skip '<<'
// 	result = malloc(sizeof(t_parsed_token)); // TODO: Add null-check
// 	result->skip = 0;
// 	result->parsed = NULL;
// 	token += 2;
// 	while (ft_isspace(*token))
// 	{
// 		token++;
// 		skip++;
// 	}
// 	if (!*token || (*token && strchr("<>", *token) && g_exit_num != 2))
// 	{
// 		printf("pipex: syntax error near unexpected token `<'\n");
// 		g_exit_num = 2;
// 		return (result);
// 	}
// 	if (*token && g_exit_num != 2)
// 	{
// 		next_symbol_idx = ft_index_of_symbol(token);
// 		if (next_symbol_idx == (size_t)-1)
// 			next_symbol_idx = ft_strlen(token);
// 		delimiter = ft_substr(token, 0, next_symbol_idx);
// 		if (pipe(pipe_fd) == -1)
// 			return (NULL); // TODO: Handle error
// 		g_exit_num = 0;
// 		while (1)
// 		{
// 			sig_manage(cfg, 2);
// 			signal(SIGQUIT, SIG_IGN);
// 			line = readline("heredoc> ");
// 			sig_manage(cfg, 1);
// 			// FIXME: !line???
// 			if (g_exit_num == 130 || !line || ft_strcmp(line, delimiter) == 0)
// 			{
// 				free(line);
// 				break ;
// 			}
// 			line = expand_super(line, cfg);
// 			write(pipe_fd[1], line, ft_strlen(line));
// 			write(pipe_fd[1], "\n", 1);
// 			free(line);
// 		}
// 		close(pipe_fd[1]);
// 		if (cmd->fd_in > 1)
// 			close(cmd->fd_in);
// 		cmd->fd_in = pipe_fd[0];
// 		skip += next_symbol_idx;
// 		free(delimiter);
// 	}
// 	result->skip = skip;
// 	return (result);
// }
