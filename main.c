/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:22:26 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 22:40:10 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_num;

static bool	is_valid_candiate(char *input)
{
	if (!input || !*input)
		return (false);
	while (*input && ft_strchr(" <>", *input))
		input++;
	if (!*input || *input == '|')
		return (false);
	while (*input && *input != '|')
		input++;
	if (*input == '|')
		return (is_valid_candiate(input + 1));
	return (true);
}

static int	enter_execution(char *input, t_shell *shell, char **splited)
{
	shell->cmds = get_cmds(shell, splited);
	if (!shell->cmds)
	{
		free(input);
		return (0);
	}
	if (shell->cmd_count == 1
		&& is_builtin(((t_cmd *)shell->cmds->content)->bin))
		shell->exit_code = handle_builtin(shell, (t_cmd *)shell->cmds->content);
	else
		ft_piped_exec(shell);
	free_cmds(shell->cmds);
	return (1);
}

static void	mini_main(char *input, t_shell *shell)
{
	char	**splited;

	add_history(input);
	if (*input && ft_strchr(input, '|') && !is_valid_candiate(input))
	{
		free(input);
		shell->exit_code = 2;
		printf("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	splited = pipe_split(input, &shell->cmd_count);
	if (is_quoted('?'))
	{
		printf("minishell: unclosed quote\n");
		close_quote();
		free_strs(splited);
	}
	else if (splited)
	{
		if (!enter_execution(input, shell, splited))
			return ;
	}
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
	int		exit_n;

	shell = initshell(envp);
	(void)argc;
	(void)argv;
	while (shell->exit_loop > -1)
	{
		g_exit_num = shell->exit_code;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_interactive);
		input = readline("> ");
		shell->exit_code = g_exit_num;
		if (!input)
			exit(1);
		else if (is_empty_arg(input))
			continue ;
		mini_main(input, shell);
	}
	free_env(shell->envp);
	exit_n = shell->exit_code;
	free(shell);
	return (exit_n);
}
