/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/16 18:17:20 by mmartine         ###   ########.fr       */
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

	// TODO: Remove this, allocate the main struct is not needed
	ret = malloc(sizeof(t_shell));
	n = 0;
	while (env[n])
		n++;
	// TODO: We need to check if the env behaves correctly in child proccesses
	alocated_env = new_env(env, n, 0, NULL);
	ret->envp = alocated_env;
	ret->cmds = NULL;
	// init_signals();
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
	signal(SIGINT, sig_manage);
	signal(SIGQUIT, sig_manage);
	while (true)
	{
		// TODO: Modify when the parser works
		input = readline("> ");
		//REVISAR ESTA LINEA PARA SABER QUE EXIT EMPLEAR
		if (!input)
			exit(1);
		if (!*input)
			continue ;
		add_history(input);
		splited = pipe_split(input, &shell->cmd_count);
		if (is_quoted('?'))
		{
			printf("pipex: unclosed quote\n");
			close_quote();
			free_strs(splited);
		}
		else if (splited)
		{
			shell->cmds = get_cmds(shell, splited);
			// print_cmds(shell->cmds, shell->cmd_count);
			if (shell->cmd_count == 1 && is_builtin(shell->cmds[0][0]))
				handle_builtin(shell);
			else
				ft_piped_exec(shell);
		}
		free_cmds((char ***)shell->cmds, shell->cmd_count);
		free(input);
	}
	return (0);
}
