/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/12 20:06:23 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_piped_exec(t_shell *shell)
{
	int	p[2];
	int	i;
	int	pid;
	int	pipe_read;
	int status;
	
	i = 0;
	pipe_read = -1;
	while (i < shell->cmd_count)
	{
		if (i < shell->cmd_count - 1 && pipe(p) == -1)
			print_error("pipe");
		pid = fork();
		if (pid == -1)
			print_error("fork");
		else if (pid == 0)
		{
			if (i > 0)
			{
				dup2(pipe_read, STDIN_FILENO);
				close(pipe_read);
			}
			if (i < shell->cmd_count - 1)
			{
				close(p[READ_END]);
				dup2(p[WRITE_END], STDOUT_FILENO);
				close(p[WRITE_END]);
			}
			if (is_builtin(shell->cmds[i][0]))
			{
				g_exit_num = handle_builtin(shell, i);
				exit(g_exit_num);
			}
			g_exit_num = execve(shell->cmds[i][0],
					(char *const *)shell->cmds[i], shell->envp);
			print_error("execve");
		}
		else
		{
			if (i > 0)
				close(pipe_read);
			if (i < shell->cmd_count - 1)
			{
				close(p[WRITE_END]);
				pipe_read = p[READ_END];
			}
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_num = WEXITSTATUS(status);
	}
}
