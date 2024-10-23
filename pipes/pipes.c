/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 13:49:51 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_piped_exec(t_shell *shell)
// {
// 	int	p[2];
// 	int	i;
// 	int	pid;
// 	int	pipe_read;

// 	i = 0;
// 	pipe_read = -1;
// 	while (i < shell->cmd_count)
// 	{
// 		if (i < shell->cmd_count - 1 && pipe(p) == -1)
// 			print_error("pipe");
// 			//signal(SIGINT, mng_hijos);
// 		pid = fork();
// 		if (pid == -1)
// 			print_error("fork");
// 		else if (pid == 0)
// 		{
// 			if (i > 0)
// 			{
// 				dup2(pipe_read, STDIN_FILENO);
// 				close(pipe_read);
// 			}
// 			if (i < shell->cmd_count - 1)
// 			{
// 				close(p[READ_END]);
// 				dup2(p[WRITE_END], STDOUT_FILENO);
// 				close(p[WRITE_END]);
// 			}
// 			if (is_builtin(shell->cmds[i][0]))
// 			{
// 				handle_builtin(shell);
// 				exit(0);
// 			}
// 			execve(shell->cmds[i][0], (char *const *)shell->cmds[i],
// 				shell->envp);
// 			print_error("execve");
// 		}
// 		else
// 		{
// 			if (i > 0)
// 				close(pipe_read);
// 			if (i < shell->cmd_count - 1)
// 			{
// 				close(p[WRITE_END]);
// 				pipe_read = p[READ_END];
// 			}
// 		}
// 		i++;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// }


void	ft_piped_exec(t_shell *shell)
{
	int	p[2];
	int	i;
	int	pid;
	int	pipe_read;

	i = 0;
	pipe_read = -1;
	while (i < shell->cmd_count)
	{
		if (i < shell->cmd_count - 1 && pipe(p) == -1)
			print_error("pipe");
			//signal(SIGINT, mng_hijos);
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
				handle_builtin(shell, i);
				exit(0);
			}
			execve(shell->cmds[i][0], (char *const *)shell->cmds[i],
				shell->envp);
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
	while (wait(NULL) > 0)
		;
}
