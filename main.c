/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/14 17:27:28 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(const char ***cmds, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (cmds[i][j])
		{
			printf("(%s)", cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	shell;
// 	char	*input;
// 	char	**splited;

// 	(void)argc;
// 	(void)argv;
// 	(void)shell;
// 	shell.cmds = NULL;
// 	shell.envp = envp;
// 	while (true)
// 	{
// 		// TODO: Modify when the parser works
// 		input = readline("> ");
// 		if (!*input)
// 			continue ;
// 		add_history(input);
// 		splited = pipe_split(input, &shell.cmd_count);
// 		if (is_quoted('?'))
// 		{
// 			printf("pipex: unclosed quote\n");
// 			return (1);
// 		}
// 		shell.cmds = get_cmds(&shell, splited);
// 		//print_cmds(shell.cmds, shell.cmd_count);
// 		// handle_builtin(shell.cmds[0]);
// 		handle_builtin(shell);

// 	}
// 	return (0);
// }

t_shell	*initshell(char **env)
{
	t_shell	*ret;
	char	**alocated_env;
	int		n;

	ret = malloc(sizeof(t_shell));
	n = 0;
	while (env[n])
		n++;
	alocated_env = new_env(env, n, 0, NULL);
	ret->envp = alocated_env;
	ret->cmds = NULL;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;
	char	**splited;

	shell = initshell(envp);
	(void)argc;
	(void)argv;
	while (true)
	{
		// TODO: Modify when the parser works
		input = readline("> ");
		if (!*input)
			continue ;
		add_history(input);
		splited = pipe_split(input, &shell->cmd_count);
		if (is_quoted('?'))
		{
			printf("pipex: unclosed quote\n");
			close_quote();	
		}
		if (splited)
		{
			shell->cmds = get_cmds(shell, splited);
			//print_cmds(shell.cmds, shell.cmd_count);
			handle_builtin(shell);
		}
	}
	return (0);
}

