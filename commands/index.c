/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 21:20:21 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(const char *cmd)
{
	int	i;
	int	num_builtins;

	static void *builtins[7] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
	};
	i = 0;
	num_builtins = 7;
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
		return (ft_env(shell));
	else if (!ft_strcmp(cmd->bin, "exit"))
		return (ft_exit(shell, cmd));
	else if (!ft_strcmp(cmd->bin, "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->bin, "unset"))
		return (ft_unset(cmd, shell));
	//99?
	return (99);
}
