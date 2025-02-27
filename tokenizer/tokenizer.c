/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <saul.blanco@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/02/18 19:31:02 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_index_of_symbol(char *str)
{
	static char	*symbols = " <>;";
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
	t_parsed_token	*other;
	char			*aux;

	next_q_idx = ft_index_of(token, quote);
	result = malloc(sizeof(t_parsed_token));
	result->parsed = ft_substr(token, 0, next_q_idx);
	if (quote == '"')
		result->parsed = expand_super(result->parsed, cfg);
	result->skip = next_q_idx + 1;
	if (token[next_q_idx + 1] == '\'' || token[next_q_idx + 1] == '"')
	{
		other = handle_quote(token + next_q_idx + 2, token[next_q_idx + 1],
				cfg);
		aux = result->parsed;
		result->parsed = ft_strjoin(aux, other->parsed);
		free(aux);
		result->skip += other->skip + 1;
		free(other->parsed);
		free(other);
	}
	else if (token[next_q_idx + 1] && !ft_isspace(token[next_q_idx + 1]))
	{
		aux = result->parsed;
		result->parsed = ft_strjoin(aux, token + next_q_idx + 1);
		free(aux);
		result->skip = ft_strlen(token);
	}
	return (result);
}

t_parsed_token	*handle_other(char *token, t_shell *cfg)
{
	size_t			next_symbol_idx;
	t_parsed_token	*result;
	char			*aux;
	char			*expanded;

	result = malloc(sizeof(t_parsed_token));
	result->skip = 0;
	next_symbol_idx = ft_index_of_symbol(token + 1);
	if (next_symbol_idx == (size_t)-1)
		next_symbol_idx = ft_strlen(token) - 1;
	result->skip = next_symbol_idx;
	aux = ft_substr(token, 0, next_symbol_idx + 1);
	expanded = expand_super(aux, cfg);
	result->parsed = ft_strdup(expanded);
	free(expanded);
	free(aux);
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
		token += 2;
	}
	while (ft_isspace(*++token))
		result->skip++;
	if (*token)
	{
		next_space_idx = ft_index_of(token, ' ');
		if (next_space_idx == (size_t)-1)
			next_space_idx = ft_strlen(token);
		// vvar auxiliar para liberar la memoria que aloja el substring
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

static char	*remove_quotes(char *str)
{
	char	*p;
	char	*end;
	char	quote;
	char	*result;

	result = ft_strdup(str);
	p = result;
	while (*p)
	{
		if (*p == '"' || *p == '\'')
		{
			quote = *p;
			end = ft_strchr(p + 1, quote);
			if (end)
			{
				ft_memmove(p, p + 1, end - p - 1);
				ft_memmove(end - 1, end + 1, ft_strlen(end));
				p = end - 2;
			}
		}
		if (p)
			p++;
	}
	return (result);
}

static char	*get_command_name(char *str)
{
	char	*temp;
	char	*space;
	char	*result;

	temp = ft_strtrim(str, "\"'");
	space = ft_strchr(temp, ' ');
	if (space)
		*space = '\0';
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

t_parsed_token	*handle_token(char *token, t_cmd *cmd, t_shell *cfg)
{
	t_parsed_token	*result;
	char			*temp;
	char			*expanded;
	size_t			symbol_idx;

	(void)cmd;
	if (token[0] == '"' || token[0] == '\'')
	{
		temp = ft_substr(token, 1, ft_strlen(token) - 2);
		result = malloc(sizeof(t_parsed_token));
		if (token[0] == '"')
		{
			expanded = expand_super(temp, cfg);
			result->parsed = ft_strdup(expanded);
			free(expanded);
		}
		else
			result->parsed = ft_strdup(temp);
		result->skip = ft_strlen(token) - 1;
		free(temp);
		return (result);
	}
	if (token[0] == '<')
	{
		if (token[1] == '<')
			return (handle_heredoc(token, cmd, cfg));
		return (handle_in_redirect(token, cmd, cfg));
	}
	if (token[0] == '>')
		return (handle_out_redirect(token, cmd, cfg));
	temp = remove_quotes(token);
	result = malloc(sizeof(t_parsed_token));
	expanded = expand_super(temp, cfg);
	result->parsed = ft_strdup(expanded);
	symbol_idx = ft_index_of_symbol(token);
	result->skip = (symbol_idx == (size_t)-1) ? ft_strlen(token)
		- 1 : symbol_idx;
	free(expanded);
	free(temp);
	return (result);
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
	cmd = malloc(sizeof(t_cmd));
	first_parsed = true;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
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
				cmd->bin = get_command_name(presult->parsed);
				ft_lstadd_back(&cmd->args, ft_lstnew(ft_strdup(cmd->bin)));
				first_parsed = false;
			}
			else
				ft_lstadd_back(&cmd->args,
					ft_lstnew(ft_strdup(presult->parsed)));
			cmd->arg_count++;
		}
		i += presult->skip + 1;
		free(presult->parsed);
		free(presult);
	}
	print_tokenized(cmd);
	return (cmd);
}
