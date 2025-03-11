/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/11 19:52:20 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_token		*handle_other(char *token, t_shell *cfg);

static inline bool	isquote(char c)
{
	return (c == '"' || c == '\'');
}

size_t	ft_index_of_symbol(char *str)
{
	static char	*symbols = " <>;'\"";
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(symbols, str[i]))
			return (i);
		i++;
	}
	return ((size_t)-1);
}

t_parsed_token	*handle_quote(char *token, char quote, t_shell *cfg)
{
	size_t			next_q_idx;
	t_parsed_token	*result;
	t_parsed_token	*othe;

	next_q_idx = ft_index_of(token, quote);
	result = malloc(sizeof(t_parsed_token));
	result->parsed = ft_substr(token, 0, next_q_idx);
	if (quote == '"')
		result->parsed = expand_super(result->parsed, cfg); // TODO: Check leak
	result->skip = next_q_idx + 1;
	if (isquote(token[next_q_idx + 1]))
	{
		othe = handle_quote(token + next_q_idx + 2, token[next_q_idx + 1], cfg);
		result->parsed = ft_strjoin(result->parsed, othe->parsed);
		result->skip += othe->skip + 1;
		free(othe);
	}
	else if (token[next_q_idx + 1] && !isspace(token[next_q_idx + 1]))
	{
		othe = handle_other(token + next_q_idx + 1, cfg);
		result->parsed = ft_strjoin(result->parsed, othe->parsed);
		result->skip += othe->skip + 1;
		free(othe);
	}
	return (result);
}

t_parsed_token	*handle_other(char *token, t_shell *cfg)
{
	size_t			next_symbol_idx;
	t_parsed_token	*result;
	t_parsed_token	*other;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	next_symbol_idx = ft_index_of_symbol(token + 1);
	if (next_symbol_idx == (size_t)-1)
		next_symbol_idx = ft_strlen(token) - 1;
	result->skip = next_symbol_idx;
	result->parsed = expand_super(ft_substr(token, 0, next_symbol_idx + 1),
			cfg);
	if (isquote(token[next_symbol_idx + 1]))
	{
		other = handle_quote(token + next_symbol_idx + 2, token[next_symbol_idx
				+ 1], cfg);
		result->parsed = ft_strjoin(result->parsed, other->parsed);
		result->skip += other->skip + 1;
		free(other);
	}
	return (result);
}

t_parsed_token	*handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			next_space_idx;
	t_parsed_token	*result;
	char			*aux;
	int				mode;
	int				fd;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 1;
	result->parsed = NULL;
	mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (token[1] == '>')
	{
		mode = O_RDWR | O_CREAT | O_APPEND;
		result->skip++;
		token ++;
	}
	while (ft_isspace(*++token))
		result->skip++;
	if (*token)
	{
		next_space_idx = ft_index_of(token, ' ');
		if (next_space_idx == (size_t) - 1)
			next_space_idx = ft_strlen(token);
		aux = ft_substr(token, 0, next_space_idx);
		fd = open(expand_super(aux, cfg), mode, 0644);
		free(aux);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_out = fd;
		result->skip += next_space_idx;
	}
	return (result);
}

// TODO: Unify with handle_out_redirect -> handle_redirect
t_parsed_token	*handle_in_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			next_space_idx;
	t_parsed_token	*result;
	char			*aux;
	int				fd;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 1;
	result->parsed = NULL;
	while (ft_isspace(*++token))
		result->skip++;
	if (*token)
	{
		next_space_idx = ft_index_of(token, ' ');
		if (next_space_idx == (size_t)-1)
			next_space_idx = ft_strlen(token);
		// si es necesario este print (no es debug) hay que asignarle el substr a aux y liberar aux
		aux = ft_substr(token, 0, next_space_idx);
		printf("Opening file: %s\n", aux);
		free(aux);
		aux = ft_substr(token, 0, next_space_idx);
		fd = open(expand_super(aux, cfg), O_RDONLY);
		free(aux);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_in = fd;
		result->skip += next_space_idx;
	}
	return (result);
}

t_parsed_token	*handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			skip;
	size_t			next_space_idx;
	t_parsed_token	*result;
	char			*delimiter;
	char			*line;
	int				pipe_fd[2];

	skip = 2; // Skip '<<'
	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	result->parsed = NULL;
	token += 2;
	while (ft_isspace(*token))
	{
		token++;
		skip++;
	}
	if (*token)
	{
		next_space_idx = ft_index_of(token, ' ');
		if (next_space_idx == (size_t)-1)
			next_space_idx = ft_strlen(token);
		delimiter = ft_substr(token, 0, next_space_idx);
		if (pipe(pipe_fd) == -1)
			return (NULL); // TODO: Handle error
		while (1)
		{
			line = readline("heredoc> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			line = expand_super(line, cfg);
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(pipe_fd[1]);
		cmd->fd_in = pipe_fd[0];
		skip += next_space_idx;
		free(delimiter);
	}
	result->skip = skip;
	return (result);
}

t_parsed_token	*handle_token(char *token, t_cmd *cmd, t_shell *cfg)
{
	(void)cmd;
	// TODO: nullcheck?
	if (token[0] == '"' || token[0] == '\'')
	{
		// handle sigle quotes, also when there is no space after
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

t_cmd	*tokenize(char *cmd_line, t_shell *cfg)
{
	size_t			i;
	size_t			len;
	t_cmd			*cmd;
	t_parsed_token	*presult;
	bool			first_parsed;

	i = 0;
	len = ft_strlen(cmd_line);
	first_parsed = true;
	cmd = init_tokenizer();
	while (i < len && cmd_line && cmd_line[i])
	{
		if (ft_isspace(cmd_line[i]))
		{
			i++;
			continue ;
		}
		presult = handle_token(&cmd_line[i], cmd, cfg);
		if (presult->parsed != NULL)
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
	print_tokenized(cmd);
	return (cmd);
}
