/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:49:39 by mmartine          #+#    #+#             */
/*   Updated: 2025/01/21 16:42:42 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_env_format(t_shell *shell, char **env, t_cmd *cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (env[++i])
	{
		aux = ft_get_env_name(env[i]);
		ft_putstr_fd("declare -x ", cmd->fd_out);
		ft_putstr_fd(aux, cmd->fd_out);
		ft_putstr_fd("=\"", cmd->fd_out);
		ft_putstr_fd(ft_get_env_val(shell, aux), cmd->fd_out);
		ft_putstr_fd("\"\n", cmd->fd_out);
		free(aux);
	}
}

void	print_sorted_env(t_shell *shell, char **env, int n, t_cmd *cmd)
{
	int			sorted;
	char		*aux;
	int			i;

	sorted = 0;
	while (!sorted)
	{
		i = -1;
		sorted = 1;
		while (++i + 1 < n)
		{
			if (ft_strcmp((const char *)env[i], (const char *)env[i + 1]) > 0)
			{
				sorted = 0;
				aux = env[i];
				env[i] = env[i + 1];
				env[i + 1] = aux;
			}
		}
	}
	printf_env_format(shell, env, cmd);
}

char	**new_env(char **env, int n, int add, char *val)
{
	char	**cpy;
	int		i;

	i = -1;
	if (add && val)
	{
		cpy = malloc(sizeof(char *) * (n + 2));
		cpy[n + 1] = NULL;
		cpy[n] = ft_strdup(val);
	}
	else
	{
		cpy = malloc(sizeof(char *) * (n + 1));
		cpy[n] = NULL;
	}
	while (++i < n)
		cpy[i] = ft_strdup(env[i]);
	return (cpy);
}
