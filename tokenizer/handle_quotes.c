/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:02:34 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/31 14:47:57 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_token		*handle_other(char *token, t_shell *cfg);

static inline bool	isquote(char c)
{
	return (c == '"' || c == '\'');
}

void	find_quote(t_parsed_token *result, char *token,
	t_shell *cfg, size_t next_q_idx)
{
	t_parsed_token	*other;
	char			*aux;

	if (isquote(token[next_q_idx + 1]))
	{
		other = handle_quote(token + next_q_idx + 2,
				token[next_q_idx + 1], cfg);
		aux = result->parsed;
		result->parsed = ft_strjoin(aux, other->parsed);
		free(aux);
		result->skip += other->skip + 1;
		free(other->parsed);
		free(other);
	}
	else if (token[next_q_idx + 1] && !isspace(token[next_q_idx + 1]))
	{
		other = handle_other(token + next_q_idx + 1, cfg);
		aux = result->parsed;
		result->parsed = ft_strjoin(aux, other->parsed);
		free(aux);
		result->skip += other->skip + 1;
		free(other->parsed);
		free(other);
	}
}

t_parsed_token	*handle_quote(char *token, char quote, t_shell *cfg)
{
	size_t			next_q_idx;
	t_parsed_token	*result;
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
	find_quote(result, token, cfg, next_q_idx);
	return (result);
}

void	found_other_quote(t_parsed_token *result,
	t_parsed_token *other, char *aux)
{
	aux = ft_strjoin(result->parsed, other->parsed);
	free(other->parsed);
	free(result->parsed);
	result->parsed = aux;
	result->skip += other->skip + 1;
	free(other);
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
		found_other_quote(result, other, aux);
	}
	return (result);
}
