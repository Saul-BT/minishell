/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/30 21:52:53 by mmartine         ###   ########.fr       */
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
	free(shell->envp[pos]);
	return (new_env);
}

int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	char	**env;

	if (cmd->args->next && cmd->args->next->content
		&& ((char *)cmd->args->next->content)[0] == '-')
	{
		printf("minishell: unset: %s: invalid option\n",
			(char *)cmd->args->next->content);
		return (2);
	}
	env = ft_delete_env_var(shell, shell->envp,
			(char *)cmd->args->next->content);
	if (env)
	{
		free(shell->envp);
		shell->envp = env;
		return (0);
	}
	return (1);
}
