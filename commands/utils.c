/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:10:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/09/04 19:27:57 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_env_pos(t_shell *shell, char *var)
{
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(var, shell->envp[i], ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free (env);
}

char	*ft_get_env_val(t_shell *shell, char *var)
{
	char	**env;
	int		i;

	i = 0;
	env = shell->envp;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
			return (env[i] + ft_strlen(var) + 1);
		i++;
	}
	return (NULL);
}

void	ft_set_env_val(t_shell *shell, char *var, char *mod)
{
	int		i;
	int		found;
	char	*new;
	char	*new2;

	i = 0;
	found = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(var, shell->envp[i], ft_strlen(var)))
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found)
	{
		new = ft_strjoin(var, "=");
		new2 = ft_strjoin(new, mod);
		free(new);
		free(shell->envp[i]);
		shell->envp[i] = new2;
	}
}