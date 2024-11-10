/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/23 14:22:56 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	handle_builtin(const char **cmd)
// {
// 	int	i;
// 	int	num_builtins;

// 	static void *map[7][2] = {
// 		{"cd", &ft_cd},
// 		{"/usr/bin/echo", &ft_echo},
// 		{"/usr/bin/env", &ft_env},
// 		{"exit", &ft_exit},
// 		{"export", &ft_export},
// 		{"pwd", &ft_pwd},
// 		{"unset", &ft_unset},
// 	};
// 	i = 0;
// 	num_builtins = 7;
// 	while (i < num_builtins && ft_strcmp(cmd[0], map[i][0]) != 0)
// 		i++;
// 	if (i < num_builtins)
// 		((void (*)(const char **))map[i][1])(cmd + 1);
// }

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

// void	handle_builtin(t_shell *shell)
// {
// 	int	i;
// 	int	num_builtins;

// 	static void *map[7][2] = {
// 		{"cd", &ft_cd},
// 		{"/usr/bin/echo", &ft_echo},
// 		{"/usr/bin/env", &ft_env},
// 		{"exit", &ft_exit},
// 		{"export", &ft_export},
// 		{"/usr/bin/pwd", &ft_pwd},
// 		{"unset", &ft_unset},
// 	};
// 	i = 0;
// 	num_builtins = 7;
// 	// printf("entramos en: %s\n", shell.cmds[0][0]);
// 	while (i < num_builtins && ft_strcmp(shell->cmds[0][0], map[i][0]) != 0)
// 		i++;
// 	if (i < num_builtins)
// 	{
// 		((void (*)(t_shell *))map[i][1])(shell);
// 	}
// }

int	handle_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->bin, "cd"))
		return (ft_cd(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->bin, "env"))
		return (ft_env(shell));
	else if (!ft_strcmp(cmd->bin, "exit"))
		return (ft_exit(shell));
	else if (!ft_strcmp(cmd->bin, "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->bin, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->bin, "unset"))
		return (ft_unset(cmd, shell));
	//99?
	return (99);
}
