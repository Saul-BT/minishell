/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:10:37 by mmartine          #+#    #+#             */
/*   Updated: 2024/11/23 14:23:10 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_exange(t_shell *shell, char *args)
{
	printf("---------%s\n", args);
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

// "text $var pepe"
//  0123456789
char	*expand_super(char *str, t_shell *cfg)
{
	int		dollar_idx, after_var_idx;
	char	*before_expanded;
	char	*expanded;

	// TODO: Should handle any whitespace character
	dollar_idx = ft_index_of(str, '$'); // -> 5

	if (dollar_idx == -1)
		return (str);
	before_expanded = ft_substr(str, 0, dollar_idx); // -> "text "
	after_var_idx = ft_index_of(str + dollar_idx + 1, ' '); // -> 8
	// TODO: index_of cannot return size_t
	after_var_idx = after_var_idx == -1 ? (int)ft_strlen(str) : after_var_idx + dollar_idx + 1;
	expanded = str_exange(cfg, ft_substr(str + dollar_idx + 1, 0, after_var_idx - dollar_idx));
	expanded = ft_strjoin(before_expanded, expanded);
	expanded = ft_strjoin(expanded, expand_super(str + after_var_idx, cfg));
	free(str);
	
	return (expanded);
}
