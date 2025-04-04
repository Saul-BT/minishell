/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <saul.blanco@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:10:29 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/01 22:06:37 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_env_pos(char **env, char *var)
{
	int		i;
	size_t	n;
	char	*name;
	char	*aux;

	i = 0;
	name = ft_get_env_name(var);
	while (env[i])
	{
		aux = ft_get_env_name(env[i]);
		n = ft_strlen(aux);
		if (ft_strlen(name) > n)
			n = ft_strlen(name);
		if (!ft_strncmp(name, env[i], n))
		{
			free(aux);
			free(name);
			return (i);
		}
		free(aux);
		i++;
	}
	free(name);
	return (-1);
}

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

char	*ft_get_env_name(char *arg)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = -1;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_calloc(sizeof(char), i + 1);
	while (++j < i)
		name[j] = arg[j];
	return (name);
}

char	*ft_get_env_val(t_shell *shell, char *var)
{
	int		i;
	size_t	n;
	char	*aux;
	char	**env;

	i = 0;
	env = shell->envp;
	while (env[i])
	{
		aux = ft_get_env_name(env[i]);
		n = ft_strlen(aux);
		if (ft_strlen(var) > n)
			n = ft_strlen(var);
		if (!ft_strncmp(var, env[i], n))
		{
			free(aux);
			return (env[i] + ft_strlen(var) + 1);
		}
		free(aux);
		i++;
	}
	return (NULL);
}

void	ft_set_env_val(t_shell *shell, char *var, char *mod, int pos)
{
	char	*new;
	char	*name;

	if (mod == NULL || pos == -1)
		return ;
	name = ft_get_env_name(var);
	new = ft_strjoin(name, "=");
	free(name);
	name = ft_strjoin(new, mod);
	free(new);
	free(shell->envp[pos]);
	shell->envp[pos] = name;
}
