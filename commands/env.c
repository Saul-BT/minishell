/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 22:27:09 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	int		j;
	char	**env;

	env = shell->envp;
	j = 0;
	if (!env)
		return (1);
	while (env[j])
	{
		if (ft_strchr(env[j], '='))
		{
			ft_putstr_fd(env[j], cmd->fd_out);
			ft_putchar_fd('\n', cmd->fd_out);
		}
		j++;
	}
	return (0);
}
