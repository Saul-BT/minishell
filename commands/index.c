/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 20:49:13 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(const char *cmd)
{
	int	i;
	int	num_builtins;

	static void *builtins[7] = {
		"cd",
		"/usr/bin/echo",
		"/usr/bin/env",
		"exit",
		"export",
		"/usr/bin/pwd",
		"unset",
	};
	i = 0;
	num_builtins = 7;
	while (i < num_builtins && ft_strcmp(cmd, builtins[i]) != 0)
		i++;
	return (i < num_builtins);
}

int	handle_builtin(t_shell *shell, int argnum)
{
	if (!ft_strcmp((shell->cmds[argnum][0]), "cd"))
		return (ft_cd(shell, argnum));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/echo"))
		return (ft_echo(shell, argnum));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/env"))
		return (ft_env(shell));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "exit"))
		return (ft_exit(shell, argnum));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "export"))
		return (ft_export(shell, argnum));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp((shell->cmds[argnum][0]), "unset"))
		return (ft_unset(shell, argnum));
	//99?
	return (99);
}
