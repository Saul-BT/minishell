/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 13:55:09 by mmartine         ###   ########.fr       */
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

void	handle_builtin(t_shell *shell, int argnum)
{
	if (!ft_strcmp((shell->cmds[argnum][0]), "cd"))
		ft_cd(shell, argnum);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/echo"))
		ft_echo(shell, argnum);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/env"))
		ft_env(shell);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "exit"))
		ft_exit(shell);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "export"))
		ft_export(shell, argnum);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "/usr/bin/pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp((shell->cmds[argnum][0]), "unset"))
		ft_unset(shell, argnum);
}
