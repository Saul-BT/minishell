/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2024/04/14 22:46:50 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->cmds = NULL;

	while (1)
	{
		// TODO: Modify when the parser works
		shell->cmds = get_cmds(shell, readline("> "));
		handle_builtin(shell);
	}
	return (0);
}
