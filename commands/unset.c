/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/10 22:16:41 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_delete_env_var(t_shell *shell, char **env, char *var)
{
	char	**new_env;
	int		pos;
	int		n;
	int		i;

	n = 0;
	i = -1;
	pos = ft_get_env_pos(shell->envp, var);
	if (pos < 0)
		return (NULL);
	while (env[n])
		n++;
	new_env = malloc(sizeof(char *) * n);
	new_env[--n] = NULL;
	while (++i < pos)
		new_env[i] = env[i];
	while (i < n)
	{
		new_env[i] = env[i + 1];
		i++;
	}
	return (new_env);
}

void	ft_unset(t_shell *shell)
{
	char	**env;

	env = ft_delete_env_var(shell, shell->envp, (char *)shell->cmds[0][1]);
	if (env)
	{
		free(shell->envp);
		shell->envp = env;
	}
}
