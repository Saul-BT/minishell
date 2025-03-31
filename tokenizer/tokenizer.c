/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/31 19:40:50 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		parsed = handle_other(cmd_line + i, cfg);
	result = ft_strjoin(parsed->parsed, cmd_line + i + parsed->skip + 1);
	free(parsed->parsed);
	free(parsed);
	return (result);
}

void	tokenize_loop_content(bool *first_parsed, t_cmd *cmd, t_parsed_token *presult)
{
	if (*first_parsed)
	{
		cmd->bin = presult->parsed;
		*first_parsed = false;
	}
	ft_lstadd_back(&cmd->args, ft_lstnew(presult->parsed));
	cmd->arg_count++;
}

t_cmd	*tokenize(char *cmd_line, t_shell *cfg, bool first_parsed)
{
	size_t			i;
	size_t			len;
	t_cmd			*cmd;
	t_parsed_token	*presult;
	char			*expanded;

	i = 0;
	expanded = expand_first(cmd_line, cfg);
	cmd = init_tokenizer(&len, expanded);
	while (i < len && expanded && expanded[i])
	{
		if (ft_isspace(expanded[i]))
		{
			i++;
			continue ;
		}
		presult = handle_token(&expanded[i], cmd, cfg);
		if (presult->parsed != NULL) // TODO: Handle error in else branch
			tokenize_loop_content(&first_parsed, cmd, presult);
		i += presult->skip + 1;
		free(presult);
	}
	free(expanded);
	print_tokenized(cmd);
	return (cmd);
}

// t_cmd	*tokenize(char *cmd_line, t_shell *cfg, bool first_parsed)
// {
// 	size_t			i;
// 	size_t			len;
// 	t_cmd			*cmd;
// 	t_parsed_token	*presult;
// 	char			*expanded;

// 	i = 0;
// 	expanded = expand_first(cmd_line, cfg);
// 	cmd = init_tokenizer(&len, expanded);
// 	while (i < len && expanded && expanded[i])
// 	{
// 		if (ft_isspace(expanded[i]))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		presult = handle_token(&expanded[i], cmd, cfg);
// 		if (presult->parsed != NULL) // TODO: Handle error in else branch
// 		{
// 			if (first_parsed)
// 			{
// 				cmd->bin = presult->parsed;
// 				first_parsed = false;
// 			}
// 			ft_lstadd_back(&cmd->args, ft_lstnew(presult->parsed));
// 			cmd->arg_count++;
// 		}
// 		i += presult->skip + 1;
// 		free(presult);
// 	}
// 	free(expanded);
// 	print_tokenized(cmd);
// 	return (cmd);
// }
