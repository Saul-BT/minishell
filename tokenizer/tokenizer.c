/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/21 03:18:51 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_token *handle_dquote(char *token, t_shell *cfg)
{
	size_t next_dquote_idx;
	t_parsed_token *result;

	next_dquote_idx = ft_index_of(token + 1, '"');
	result = malloc(sizeof(t_parsed_token));
	result->parsed = expand_super(ft_substr(token + 1, 0, next_dquote_idx), cfg);
	result->skip = next_dquote_idx + 1;

	return (result);
}

t_parsed_token *handle_quote(char *token)
{
	size_t next_quote_idx;
	t_parsed_token *result;

	next_quote_idx = ft_index_of(token + 1, '\'');
	result = malloc(sizeof(t_parsed_token));
	result->parsed = ft_substr(token + 1, 0, next_quote_idx);
	result->skip = next_quote_idx + 1;

	return (result);
}

t_parsed_token *handle_other(char *token, t_shell *cfg)
{
	size_t 			next_space_idx;
	t_parsed_token	*result;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	next_space_idx = ft_index_of(token + 1, ' ');
	if (next_space_idx == (size_t)-1)
		next_space_idx = ft_strlen(token) - 1;
	result->skip = next_space_idx;
	result->parsed = expand_super(ft_substr(token, 0, next_space_idx + 1), cfg);
	return (result);
}

t_parsed_token *handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t skip;
	size_t next_space_idx;
	t_parsed_token *result;
	char	*aux;
	
	skip = 1;
	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	result->parsed = NULL;

	token++;
	int mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (token[0] == '>')
	{
		mode = O_RDWR | O_CREAT | O_APPEND;
		skip++;
		token++;
	}

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
		//vvar auxiliar para liberar la memoria que aloja el substring
		aux = ft_substr(token, 0, next_space_idx);
		int fd = open(expand_super(aux, cfg), mode, 0644);
		free(aux);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_out = fd;
		skip += next_space_idx;
	}
	result->skip = skip;
	return (result);
}

// TODO: Unify with handle_out_redirect -> handle_redirect
t_parsed_token *handle_in_redirect(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t skip;
	size_t next_space_idx;
	t_parsed_token *result;
	char	*aux;

	skip = 1;
	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	result->parsed = NULL;

	token++;
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
		//si es necesario este print (no es debug) hay que asignarle el substr a aux y liberar aux
		aux = ft_substr(token, 0, next_space_idx);
		printf("Opening file: %s\n", aux);
		free(aux);
		aux = ft_substr(token, 0, next_space_idx);
		int fd = open(expand_super(aux, cfg), O_RDONLY);
		// if (fd == -1)
		// TODO: Handle error
		cmd->fd_in = fd;
		skip += next_space_idx;
		free(aux);
	}
	result->skip = skip;
	return (result);
}

t_parsed_token *handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t skip;
	size_t next_space_idx;
	t_parsed_token *result;
	char *delimiter;
	char *line;
	int pipe_fd[2];

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
				break;
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

t_parsed_token *handle_token(char *token, t_cmd *cmd, t_shell *cfg)
{
	(void)cmd;
	// TODO: nullcheck?
	if (token[0] == '"')
	{
		// handle double quotes, also when there is no space after
		return (handle_dquote(token, cfg));
	}
	if (token[0] == '\'')
	{
		// handle sigle quotes, also when there is no space after
		return (handle_quote(token));
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

void print_arg(char *arg)
{
	printf("  -> %s\n", arg);
}

void print_tokenized(t_cmd *cmd)
{
	printf("\033[0;34m=====================\n");
	printf("bin: %s\n", cmd->bin);
	printf("arg_count: %d\n", cmd->arg_count);
	ft_lstiter(cmd->args, (void (*)(void *))print_arg);
	printf("=====================\033[0m\n");
}

t_cmd *tokenize(char *cmd_line, t_shell *cfg)
{
	size_t i;
	size_t len;
	t_cmd *cmd;
	t_parsed_token *presult;
	bool first_parsed;

	i = 0;
	len = ft_strlen(cmd_line);
	cmd = malloc(sizeof(t_cmd));
	first_parsed = true;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	while (i < len && cmd_line && cmd_line[i])
	{
		// If is space -> skip
		if (ft_isspace(cmd_line[i]))
		{
			i++;
			continue;
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
		//algunos leaks se arreglan con la linea de debajo de esta. No se si rompo algo.
		free(presult);
	}

	// print_tokenized(cmd);

	return (cmd);
}
