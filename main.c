/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/20 20:27:49 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_num;

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

void	check_shlvl( int n, t_shell *shell)
{
	int		lvl;
	int		pos;
	char	*aux;

	lvl = 0;
	pos = ft_get_env_pos(shell->envp, "SHLVL");
	if (pos > 0)
	{
		lvl = ft_atoi(ft_get_env_val(shell, "SHLVL"));
		lvl++;
		aux = ft_itoa(lvl);
		ft_set_env_val(shell, "SHLVL", aux, pos);
		free(aux);
	}
	else
	{
		new_env(shell->envp, n + 1, 1, "SHLVL");
		ft_set_env_val(shell, "SHLVL", "1",
			ft_get_env_pos(shell->envp, "SHLVL"));
	}
}

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
	if (*env)
	{
		alocated_env = new_env(env, n, 0, NULL);
		ret->envp = alocated_env;
		check_shlvl(n, ret);
	}

	ret->cmds = NULL;
	ret->exit_code = 0;
	// init_signals();
	g_exit_num = 0;
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
	// signal(SIGINT, sig_manage);
	// signal(SIGQUIT, sig_manage);
	while (!shell->exit_code)
	{
		sig_manage(shell, 1);
		// write_signals(shell, false);
		// TODO: Modify when the parser works
		input = readline("> ");
		sig_manage(shell, 0);
		// write_signals(shell, true);
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
			if (shell->cmd_count == 1 && is_builtin(((t_cmd *)shell->cmds->content)->bin))
				g_exit_num = handle_builtin(shell, (t_cmd *)shell->cmds->content);
			else
				ft_piped_exec(shell);
		}
		free_cmds(shell->cmds);
		free(input);
	}
	return (g_exit_num);
}
