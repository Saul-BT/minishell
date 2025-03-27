/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <saul.blanco@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/27 19:12:55 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(const char *cmd)
{
	int			i;
	int			num_builtins;
	static void	*builtins[7];

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	i = 0;
	num_builtins = 7;
	if (!cmd)
		return (false);
	while (i < num_builtins && ft_strcmp(cmd, builtins[i]) != 0)
		i++;
	return (i < num_builtins);
}

int	handle_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->bin, "cd"))
		return (ft_cd(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->bin, "env"))
		return (ft_env(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "exit"))
		return (ft_exit(shell, cmd));
	else if (!ft_strcmp(cmd->bin, "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "pwd"))
		return (ft_pwd(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "unset"))
		return (ft_unset(cmd, shell));
	return (99);
}
