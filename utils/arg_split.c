/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:56:48 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/15 17:01:05 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// echo "hola mundo"
static int	count_tokens(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str && is_space(*str))
		str++;
	while (*str)
	{
		if (!is_quoted(*str) && is_space(*str))
		{
			count++;
			while (*str && is_space(*str))
				str++;
		}
		else
			str++;
	}
	if (is_space(*(str - 1)))
		count--;
	return (count);
}

static void set_tokens(const char *str, char ***tokens, int token_count)
{
	size_t i = 0;
	int count = 0;
	bool isspace = false;
	size_t wb_index = 0;
	size_t token_start_index = 0;

	while (str[i] && is_space(str[i]))
		i++;
	while (i <= ft_strlen(str))
	{
		isspace = is_space(str[i]);
		if (is_quoted(str[i]))
			isspace = false;
		if (i > 0 && is_word_boundary(str[i - 1], str[i]))
			wb_index = i;
		if (count > 0 && token_start_index == 0 && !isspace && is_word_boundary(str[i], str[i - 1]))
			token_start_index = i;
		if (isspace || !str[i])
		{
			printf("substr: %ld, %ld - %ld (%ld)\n", token_start_index, wb_index, token_start_index, wb_index - token_start_index);
			if (count == token_count - 1)
			{
				(*tokens)[count++] = ft_substr(str, token_start_index, ft_strlen(str) - token_start_index);
			}
			else
				(*tokens)[count++] = ft_substr(str, token_start_index, wb_index - token_start_index);
			token_start_index = 0;
			while (str[i] && is_space(str[i]))
				i++;
		}
		else
			i++;
	}
}

void	test(const char *str)
{
	int token_count = count_tokens(str) + 1;
	char **tokens = ft_calloc(token_count + 1, sizeof(char *));

	set_tokens(str, &tokens, token_count);

	for (int i = 0; i < token_count; i++)
		printf("Token nº%d is '%s'\n", i, tokens[i]);
}
