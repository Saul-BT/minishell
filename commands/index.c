/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:29:32 by sblanco-          #+#    #+#             */
/*   Updated: 2024/04/15 08:28:00 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_shell *shell)
{
	int		i;
	int		num_builtins;
	void	*map[7][2];

	i = 0;
	num_builtins = 7;
	map[0][0] = "cd";
	map[0][1] = &ft_cd;
	map[1][0] = "echo";
	map[1][1] = &ft_echo;
	map[2][0] = "env";
	map[2][1] = &ft_env;
	map[3][0] = "exit";
	map[3][1] = &ft_exit;
	map[4][0] = "export";
	map[4][1] = &ft_export;
	map[5][0] = "pwd";
	map[5][1] = &ft_pwd;
	map[6][0] = "unset";
	map[6][1] = &ft_unset;
	while (i < num_builtins && ft_strcmp(shell->input, map[i][0]) != 0)
		i++;
	if (i < num_builtins)
		((void (*)(t_shell *))map[i][1])(shell);
}
