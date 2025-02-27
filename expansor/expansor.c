/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <saul.blanco@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:10:37 by mmartine          #+#    #+#             */
/*   Updated: 2025/02/18 19:22:39 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_exange(t_shell *shell, char *args)
{
	char	*value;
	char	*result;

	if (args[1] == '?')
		return (ft_itoa(g_exit_num));
	else if (!args[1])
		return (ft_strdup("$"));
	else
	{
		if (ft_get_env_pos(shell->envp, args + 1) < 0)
			return (ft_strdup(""));
		value = ft_get_env_val(shell, args + 1);
		result = ft_strdup(value);
		return (result);
	}
	free(args);
}

char	**expand(t_shell *shell, char **args)
{
	int		i;
	char	*substitute;

	i = 0;
	while (args[i])
	{
		if (*args[i] == '$')
		{
			substitute = ft_strdup(args[i]);
			free(args[i]);
			// TODO: Check the following:
			// $ export test="test"
			// $ echo $test
			// "test" <- wrong output, maybe we should call handle_quote (?)
			args[i] = str_exange(shell, substitute);
		}
		i++;
	}
	return (args);
}

char	*expand_super(char *str, t_shell *cfg)
{
	size_t	dollar_idx;
	size_t	after_var_idx;
	char	*before_expanded;
	char	*expanded;
	char	*aux;
	char	*result;

	dollar_idx = ft_index_of(str, '$');
	if (dollar_idx == (size_t)-1)
		return (ft_strdup(str));
	before_expanded = ft_substr(str, 0, dollar_idx);
	after_var_idx = ft_index_of(str + dollar_idx + 1, ' ');
	if (after_var_idx == (size_t)-1)
		after_var_idx = ft_strlen(str);
	else
		after_var_idx += dollar_idx + 1;
	aux = ft_substr(str + dollar_idx, 0, after_var_idx - dollar_idx);
	expanded = str_exange(cfg, aux);
	free(aux);
	aux = ft_strjoin(before_expanded, expanded);
	free(before_expanded);
	free(expanded);
	result = ft_strjoin(aux, expand_super(str + after_var_idx, cfg));
	free(aux);
	return (result);
}
