/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    main_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:34:08 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/03 20:39:53 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_shlvl(int n, t_shell *shell)
{
	int		lvl;
	int		pos;
	char	*aux;
	char	**env;

	lvl = 0;
	pos = ft_get_env_pos(shell->envp, "SHLVL");
	if (pos > 0)
	{
		lvl = ft_atoi(ft_get_env_val(shell, "SHLVL"));
		lvl++;
		aux = ft_itoa(lvl);
		ft_set_env_val(shell, "SHLVL", aux, pos);
		free(aux);
	}
	else
	{
		env = new_env(shell->envp, n, 1, "SHLVL");
		free_env(shell->envp);
		shell->envp = env;
		ft_set_env_val(shell, "SHLVL", "1", ft_get_env_pos(shell->envp,
				"SHLVL"));
	}
}

t_shell	*initshell(char **env)
{
	t_shell	*ret;
	char	**alocated_env;
	int		n;

	ret = malloc(sizeof(t_shell));
	n = 0;
	while (*env && env[n])
		n++;
	alocated_env = new_env(env, n, 0, NULL);
	ret->envp = alocated_env;
	if (n == 0)
		n = 2;
	check_shlvl(n, ret);
	ret->cmds = NULL;
	ret->exit_code = 0;
	g_exit_num = 0;
	return (ret);
}
