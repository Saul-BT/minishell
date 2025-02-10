/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:10:37 by mmartine          #+#    #+#             */
/*   Updated: 2025/01/21 16:44:17 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_exange(t_shell *shell, char *args)
{
	if (args[1] == '?')
		return (ft_itoa(g_exit_num));
	else if (!args[1])
		return (ft_strdup("$"));
	else
	{
		if (ft_get_env_pos(shell->envp, args + 1) < 0)
			return (ft_strdup(""));
		return (ft_strdup(ft_get_env_val(shell, args + 1)));
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
			args[i] = str_exange(shell, substitute);
		}
		i++;
	}
	return (args);
}

static void	free_expand_vars(char *before_expanded, char *str, char *aux)
{
	free(before_expanded);
	free(str);
	free(aux);
}

char	*expand_super(char *str, t_shell *cfg)
{
	size_t	dollar_idx;
	size_t	after_var_idx;
	char	*before_expanded;
	char	*expanded;
	char	*aux;

	dollar_idx = ft_index_of(str, '$');
	if (dollar_idx == (size_t)-1)
		return (str);
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
	free(expanded);
	expanded = ft_strjoin(aux, expand_super(str + after_var_idx, cfg));
	free_expand_vars(before_expanded, str, aux);
	return (expanded);
}
