/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/30 18:55:07 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_token		*handle_other(char *token, t_shell *cfg);

static inline bool	isquote(char c)
{
	return (c == '"' || c == '\'');
}

t_parsed_token	*handle_quote(char *token, char quote, t_shell *cfg)
{
	size_t			next_q_idx;
	t_parsed_token	*result;
	t_parsed_token	*other;
	char			*aux;

	next_q_idx = ft_index_of(token, quote);
	result = malloc(sizeof(t_parsed_token));
	result->parsed = ft_substr(token, 0, next_q_idx);
	if (quote == '"')
	{
		aux = expand_super(result->parsed, cfg);
		free(result->parsed);
		result->parsed = aux;
	}
	result->skip = next_q_idx + 1;
	if (isquote(token[next_q_idx + 1]))
	{
		other = handle_quote(token + next_q_idx + 2, token[next_q_idx + 1], cfg);
		result->parsed = ft_strjoin(result->parsed, other->parsed);
		result->skip += other->skip + 1;
		free(other->parsed);
		free(other);
	}
	else if (token[next_q_idx + 1] && !isspace(token[next_q_idx + 1]))
	{
		other = handle_other(token + next_q_idx + 1, cfg);
		result->parsed = ft_strjoin(result->parsed, other->parsed);
		result->skip += other->skip + 1;
		free(other->parsed);
		free(other);
	}
	return (result);
}

t_parsed_token	*handle_other(char *token, t_shell *cfg)
{
	size_t			next_symbol_idx;
	t_parsed_token	*result;
	t_parsed_token	*other;
	char			*aux;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	next_symbol_idx = ft_index_of_symbol(token + 1);
	if (next_symbol_idx == (size_t)-1)
		next_symbol_idx = ft_strlen(token) - 1;
	result->skip = next_symbol_idx;
	aux = ft_substr(token, 0, next_symbol_idx + 1);
	result->parsed = expand_super(aux, cfg);
	free(aux);
	if (isquote(token[next_symbol_idx + 1]))
	{
		other = handle_quote(token + next_symbol_idx + 2, token[next_symbol_idx
				+ 1], cfg);
		aux = ft_strjoin(result->parsed, other->parsed);
		free(other->parsed);
		free(result->parsed);
		result->parsed = aux;
		result->skip += other->skip + 1;
		free(other);
	}
	return (result);
}

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

t_parsed_token	*handle_in_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	t_parsed_token	*result;
	t_parsed_token	*other;
	int				fd;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	result->parsed = NULL;
	while (ft_isspace(*++token))
		result->skip++;
	if (!*token || (*token && *token == '>' && g_exit_num != 2))
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
		fd = open(other->parsed, O_RDONLY);
		free(other->parsed);
		free(other);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_in = fd;
	}
	return (result);
}

t_parsed_token	*handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			skip;
	size_t			next_symbol_idx;
	t_parsed_token	*result;
	char			*delimiter;
	char			*line;
	int				pipe_fd[2];

	skip = 1;                                // Skip '<<'
	result = malloc(sizeof(t_parsed_token)); // TODO: Add null-check
	result->skip = 0;
	result->parsed = NULL;
	token += 2;
	while (ft_isspace(*token))
	{
		token++;
		skip++;
	}
	if (!*token || (*token && strchr("<>", *token) && g_exit_num != 2))
	{
		printf("pipex: syntax error near unexpected token `<'\n");
		g_exit_num = 2;
		return (result);
	}
	if (*token && g_exit_num != 2)
	{
		next_symbol_idx = ft_index_of_symbol(token);
		if (next_symbol_idx == (size_t)-1)
			next_symbol_idx = ft_strlen(token);
		delimiter = ft_substr(token, 0, next_symbol_idx);
		if (pipe(pipe_fd) == -1)
			return (NULL); // TODO: Handle error
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
			// TODO: Check to remove
			// if (!*line)
			//{
			//	free(line);
			//	continue ;
			//}
			line = expand_super(line, cfg);
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(pipe_fd[1]);
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		cmd->fd_in = pipe_fd[0];
		skip += next_symbol_idx;
		free(delimiter);
	}
	result->skip = skip;
	return (result);
}

t_parsed_token	*handle_token(char *token, t_cmd *cmd, t_shell *cfg)
{
	(void)cmd;
	if (token[0] == '"' || token[0] == '\'')
	{
		return (handle_quote(token + 1, token[0], cfg));
	}
	if (token[0] == '<')
	{
		if (token[1] == '<')
		{
			return (handle_heredoc(token, cmd, cfg));
		}
		return (handle_in_redirect(token, cmd, cfg));
	}
	if (token[0] == '>')
	{
		return (handle_out_redirect(token, cmd, cfg));
	}
	return (handle_other(token, cfg));
}

void	print_arg(char *arg)
{
	printf("  -> %s\n", arg);
}

void	print_tokenized(t_cmd *cmd)
{
	printf("\033[0;34m=====================\n");
	printf("bin: %s\n", cmd->bin);
	printf("arg_count: %d\n", cmd->arg_count);
	ft_lstiter(cmd->args, (void (*)(void *))print_arg);
	printf("redirections:\n");
	printf("  -> fd_in: %d\n", cmd->fd_in);
	printf("  -> fd_out: %d\n", cmd->fd_out);
	printf("=====================\033[0m\n");
}

char	*expand_first(char *cmd_line, t_shell *cfg)
{
	size_t			i;
	char			*result;
	t_parsed_token	*parsed;

	i = 0;
	while (ft_isspace(cmd_line[i]))
		i++;
	if (ft_strchr("'\"", cmd_line[i]))
		parsed = handle_quote(cmd_line + i + 1, cmd_line[i], cfg);
	else
		parsed = handle_other(cmd_line, cfg);
	result = ft_strjoin(parsed->parsed, cmd_line + i + parsed->skip + 1);
	free(parsed);
	return (result);
}

t_cmd	*tokenize(char *cmd_line, t_shell *cfg)
{
	size_t			i;
	size_t			len;
	t_cmd			*cmd;
	t_parsed_token	*presult;
	char			*expanded;
	bool			first_parsed;

	i = 0;
	expanded = expand_first(cmd_line, cfg);
	len = ft_strlen(expanded);
	first_parsed = true;
	cmd = init_tokenizer();
	while (i < len && expanded && expanded[i])
	{
		if (ft_isspace(expanded[i]))
		{
			i++;
			continue ;
		}
		presult = handle_token(&expanded[i], cmd, cfg);
		if (presult->parsed != NULL) // TODO: Handle error in else branch
		{
			if (first_parsed)
			{
				cmd->bin = presult->parsed;
				first_parsed = false;
			}
			ft_lstadd_back(&cmd->args, ft_lstnew(presult->parsed));
			cmd->arg_count++;
		}
		i += presult->skip + 1;
		free(presult);
	}
	free(expanded);
	print_tokenized(cmd);
	return (cmd);
}
