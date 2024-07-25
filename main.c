/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 17:26:16 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char *input;

	(void)argc;
	(void)argv;
	(void)shell;
	shell.cmds = NULL;
	shell.envp = envp;

	while (true)
	{
		// TODO: Modify when the parser works
		input = ft_strtrim(readline("> "), " \t\n\v\f\r");
		
		if (!*input)
			continue;

		shell.cmds = get_cmds(&shell, pipe_split(input, &shell.cmd_count));
		handle_builtin(shell.cmds[0]);
	}
	return (0);
}
