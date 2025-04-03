/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:10:37 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/03 21:51:35 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_exange(t_shell *shell, char *args)
{
	if (args[1] == '?')
		return (ft_itoa(shell->exit_code));
	else if (!is_valid_var_start_char(args[1]))
		return (ft_strdup(args));
	else
	{
		if (ft_get_env_pos(shell->envp, args + 1) < 0)
			return (ft_strdup(""));
		return (ft_strdup(ft_get_env_val(shell, args + 1)));
	}
	free(args);
}

char	*expand_concat(size_t dollar_idx, size_t after_var_idx,
	char *str, t_shell *cfg)
{
	char	*aux;
	char	*expanded;
	char	*before_expanded;
	char	*result;

	before_expanded = ft_substr(str, 0, dollar_idx);
	aux = ft_substr(str + dollar_idx, 0, after_var_idx - dollar_idx);
	expanded = str_exange(cfg, aux);
	free(aux);
	aux = ft_strjoin(before_expanded, expanded);
	free(before_expanded);
	free(expanded);
	expanded = expand_super(str + after_var_idx, cfg);
	result = ft_strjoin(aux, expanded);
	free(aux);
	free(expanded);
	return (result);
}

size_t	get_var_boundary(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '?' && !is_valid_var_start_char(str[i]))
		return (1);
	while (str[i] && str[i] != '=' && is_valid_var_char(str[i]))
		i++;
	return (i);
}

char	*expand_super(char *str, t_shell *cfg)
{
	size_t	dollar_idx;
	size_t	after_var_idx;

	dollar_idx = ft_index_of(str, '$');
	if (dollar_idx == (size_t) - 1 || dollar_idx == ft_strlen(str) - 1)
		return (ft_strdup(str));
	after_var_idx = get_var_boundary(str + dollar_idx + 1);
	if (after_var_idx == 0)
		return (expand_concat(dollar_idx, after_var_idx + 1, str, cfg));
	else
		after_var_idx += dollar_idx + 1;
	return (expand_concat(dollar_idx, after_var_idx, str, cfg));
}
