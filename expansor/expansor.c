/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:10:37 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/17 19:01:33 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_exange(t_shell *shell, char *args)
{
	if (args[1] == '?')
		return (ft_itoa(g_exit_num));
	else
	{
		if (ft_get_env_pos(shell->envp, args + 1) < 0)
			return (ft_strdup(""));
		return (ft_strdup(ft_get_env_val(shell, args + 1)));
	}
	free(args);
}

// static void	free_expand_vars(char *before_expanded, char *str, char *aux)
// {
// 	free(before_expanded);
// 	free(str);
// 	free(aux);
// }


char	*expand_super(char *str, t_shell *cfg)
{
	size_t	dollar_idx;
	size_t	after_var_idx;
	char	*before_expanded;
	char	*expanded;
	char	*aux;
	char	*result;

	dollar_idx = ft_index_of(str, '$');
	if (dollar_idx == (size_t)-1 || dollar_idx == ft_strlen(str) - 1)
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
	expanded = expand_super(str + after_var_idx, cfg);
	result = ft_strjoin(aux, expanded);
	free(aux);
	free(expanded);
	return (result);
}