/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:12 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/09 23:24:09 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || (c == ' '));
}

t_parsed_token	*handle_dquote(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			next_dquote_idx;
	t_parsed_token	*result;
	
	next_dquote_idx = ft_index_of(token + 1, '"');
	result = malloc(sizeof(t_parsed_token));
	result->parsed = expand_super(ft_substr(token, 0, next_dquote_idx), cfg);
	result->skip = next_dquote_idx;

	return (result);
}

t_parsed_token	*handle_quote(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			next_quote_idx;
	t_parsed_token	*result;
	
	next_quote_idx = ft_index_of(token + 1, '\'');
	result = malloc(sizeof(t_parsed_token));
	result->parsed = ft_substr(token, 0, next_quote_idx);
	result->skip = next_quote_idx;

	return (result);
}

t_parsed_token	*handle_other(char *token, t_cmd *cmd, t_shell *cfg)
{
	size_t			next_space_idx;
	t_parsed_token	*result;
	
	next_space_idx = ft_index_of(token + 1, ' ');
	result = malloc(sizeof(t_parsed_token));
	result->parsed = expand_super(ft_substr(token, 0, next_space_idx), cfg);
	result->skip = next_space_idx;

	return (result);
}

t_parsed_token	*handle_token(char *token, t_cmd *cmd, t_shell *cfg)
{
	// TODO: nullcheck?
	if (token[0] == '"')
	{
		// handle double quotes, also when there is no space after
		return (handle_dquote(token, cmd, cfg));
	}
	if (token[0] == '\'')
	{
		// handle sigle quotes, also when there is no space after
		return (handle_quote(token, cmd, cfg));
	}
	if (token[0] == '<')
	{
		if (token[1] == '<') {
			
		}
	}
	if (token[0] == '>')
	{
		if (token[1] == '>') {
			
		}
	}

	return (handle_other(token, cmd, cfg));
}

t_cmd	*tokenize(char *cmd_line, t_shell *cfg)
{
	size_t			i;
	t_cmd			*cmd;
	t_parsed_token	*presult;
	bool			first_parsed;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	first_parsed = true;
	cmd->args = ft_lstnew(NULL);
	while (cmd_line && cmd_line[i])
	{
		// If is space -> skip
		if (is_space(cmd_line[i]))
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
		}
		i += presult->skip;
	}

	return cmd;
}
