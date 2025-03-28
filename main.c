/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/27 19:45:21 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_num;

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

void	check_shlvl(int n, t_shell *shell)
{
	int		lvl;
	int		pos;
	char	*aux;
	char	**env;

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
		env = new_env(shell->envp, n, 1, "SHLVL");
		free_env(shell->envp);
		shell->envp = env;
		ft_set_env_val(shell, "SHLVL", "1", ft_get_env_pos(shell->envp,
				"SHLVL"));
	}
}

t_shell	*initshell(char **env)
{
	t_shell	*ret;
	char	**alocated_env;
	int		n;

	ret = malloc(sizeof(t_shell));
	n = 0;
	while (*env && env[n])
		n++;
	alocated_env = new_env(env, n, 0, NULL);
	ret->envp = alocated_env;
	if (n == 0)
		n = 2;
	check_shlvl(n, ret);
	ret->cmds = NULL;
	ret->exit_code = 0;
	g_exit_num = 0;
	return (ret);
}

static bool	is_valid_candiate(char *input)
{
	bool	empty_before;
	bool	empty_after;

	empty_before = true;
	empty_after = true;
	if (!input || !*input)
		return (true);
	while (*input && *input != '|')
	{
		empty_before = empty_before && ft_isspace(*input);
		input++;
	}
	if (*input++ != '|')
		return (true);
	if (empty_before)
		return (false);
	while (*input && *input != '|')
	{
		empty_after = empty_after && ft_isspace(*input);
		input++;
	}
	if (empty_after && *input == '|')
		return (false);
	return (!empty_before && !empty_after);
}

static void	mini_main(char *input, t_shell *shell)
{
	char	**splited;

	add_history(input);
	if (!is_valid_candiate(input))
	{
		g_exit_num = 2;
		printf("pipex: syntax error near unexpected token `|'\n");
		return ;
	}
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
		if (!shell->cmds || (g_exit_num > 0 && g_exit_num < 130)
		{
			free(input);
			return ;
		}
		if (shell->cmd_count == 1
			&& is_builtin(((t_cmd *)shell->cmds->content)->bin))
			g_exit_num = handle_builtin(shell, (t_cmd *)shell->cmds->content);
		else
			ft_piped_exec(shell);
	}
	free_cmds(shell->cmds);
	free(input);
}

static int	is_empty_arg(char *str)
{
	char	*aux;
	int		ret;

	ret = 0;
	aux = ft_strtrim(str, " \t\r");
	if (!*aux)
	{
		ret = 1;
		free(str);
	}
	free(aux);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;

	shell = initshell(envp);
	(void)argc;
	(void)argv;
	while (shell->exit_code > -1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_interactive);
		input = readline("> ");
		// sig_manage(shell, 0);
		// REVISAR ESTA LINEA PARA SABER QUE EXIT EMPLEAR
		if (!input)
			exit(1);
		else if (is_empty_arg(input))
			continue ;
		mini_main(input, shell);
	}
	free_env(shell->envp);
	free(shell);
	return (g_exit_num);
}
