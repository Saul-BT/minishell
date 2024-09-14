/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/03 17:17:07 by mmartine         ###   ########.fr       */
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


void	handle_builtin(t_shell *shell)
{
	int	i;
	int	num_builtins;

	static void *map[7][2] = {
		{"cd", &ft_cd},
		{"/usr/bin/echo", &ft_echo},
		{"/usr/bin/env", &ft_env},
		{"exit", &ft_exit},
		{"export", &ft_export},
		{"/usr/bin/pwd", &ft_pwd},
		{"unset", &ft_unset},
	};
	i = 0;
	num_builtins = 7;
	// printf("entramos en: %s\n", shell.cmds[0][0]);
	while (i < num_builtins && ft_strcmp(shell->cmds[0][0], map[i][0]) != 0)
		i++;
	if (i < num_builtins)
	{
		((void (*)(t_shell *))map[i][1])(shell);
	}
}
