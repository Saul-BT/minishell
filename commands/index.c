/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 19:18:16 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(const char **cmd)
{
	int	i;
	int	num_builtins;

	static void *map[7][2] = {
		{"cd", &ft_cd},
		{"/usr/bin/echo", &ft_echo},
		{"/usr/bin/env", &ft_env},
		{"exit", &ft_exit},
		{"export", &ft_export},
		{"pwd", &ft_pwd},
		{"unset", &ft_unset},
	};
	i = 0;
	num_builtins = 7;
	while (i < num_builtins && ft_strcmp(cmd[0], map[i][0]) != 0)
		i++;
	if (i < num_builtins)
		((void (*)(const char **))map[i][1])(cmd + 1);
}
