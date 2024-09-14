/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/14 20:41:18 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_cmd(const char **cmd)
{
	int	i;

	i = 0;
	printf("Executing %s:\n", cmd[0]);
	while (cmd[i])
	{
		printf("%s (%d)", cmd[i], i);
		i++;
	}
	printf("\n");
}

void	ft_piped_exec(t_shell *shell)
{
	int	p[2];
	int	pid;
	int	pipe_read;
	int	i;

	// 1. Ejecutar primer comando
	if (pipe(p) == -1)
	{
		printf("minishell(pipe): error al crear pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("minishell(pipe): error al crear subproceso");
		return ;
	}
	print_cmd(shell->cmds[0]);
	if (pid == 0)
	{
		close(p[READ_END]);
		dup2(p[WRITE_END], STDOUT_FILENO);
		close(p[WRITE_END]);
		execve(shell->cmds[0][0], (char *const *)shell->cmds[0], shell->envp);
		printf("minishell: error al ejecutar primer comando");
		exit(1);
	}
	close(p[WRITE_END]);
	// 2. Ejecutar comandos intermedios
	i = 1;
	while (i < shell->cmd_count - 2)
	{
		pipe_read = p[READ_END];
		print_cmd(shell->cmds[i]);
		if (pipe(p) == -1)
		{
			printf("minishell(pipe): error al crear pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			printf("minishell(pipe): error al crear subproceso");
			return ;
		}
		if (pid == 0)
		{
			dup2(pipe_read, STDIN_FILENO);
			dup2(p[WRITE_END], STDOUT_FILENO);
			close(pipe_read);
			close(p[READ_END]);
			close(p[WRITE_END]);
			execve(shell->cmds[i][0], (char *const *)shell->cmds[i],
				shell->envp);
			printf("minishell: error al ejecutar comando intermedio");
			exit(1);
		}
		close(pipe_read);
		close(p[WRITE_END]);
		i++;
	}
	// 3. Ejecutar último comando
	pid = fork();
	if (pid == -1)
	{
		printf("minishell(pipe): error al crear subproceso");
		return ;
	}
	print_cmd(shell->cmds[shell->cmd_count - 1]);
	if (pid == 0)
	{
		close(p[WRITE_END]);
		dup2(p[READ_END], STDIN_FILENO);
		close(p[READ_END]);
		execve(shell->cmds[shell->cmd_count - 1][0],
			(char *const *)shell->cmds[shell->cmd_count - 1], shell->envp);
		printf("minishell: error al ejecutar primer comando");
		exit(1);
	}
	close(p[READ_END]);
	close(p[WRITE_END]);
}
