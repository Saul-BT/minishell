/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/22 05:03:04 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**arg_nodes_to_arg_array(t_cmd *cmd)
{
	int		i;
	t_node	*arg_node;
	char	**result;

	i = 0;
	arg_node = cmd->args;
	result = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	while (i < cmd->arg_count && arg_node)
	{
		result[i] = (char *)arg_node->content;
		arg_node = arg_node->next;
		i++;
	}
	return (result);
}

// void	ft_piped_exec(t_shell *shell)
// {
// 	int		p[2];
// 	int		i;
// 	int		pid;
// 	int		pipe_read;
// 	int		status;
// 	t_node	*cmd_node;
// 	t_cmd	*cmd;
// 	char	**args;

// 	i = 0;
// 	pipe_read = -1;
// 	cmd_node = shell->cmds;
// 	while (i < shell->cmd_count && cmd_node)
// 	{
// 		cmd = (t_cmd *)cmd_node->content;
// 		if (i < shell->cmd_count - 1 && pipe(p) == -1)
// 			print_error("pipe");
// 		// signal(SIGINT, mng_hijos);
// 		pid = fork();
// 		if (pid == -1)
// 			print_error("fork");
// 		else if (pid == 0)
// 		{
// 			if (i > 0)
// 			{
// 				dup2(pipe_read, cmd->fd_in);
// 				close(pipe_read);
// 			}
// 			if (i < shell->cmd_count - 1)
// 			{
// 				close(p[READ_END]);
// 				dup2(p[WRITE_END], cmd->fd_out);
// 				close(p[WRITE_END]);
// 			}
// 			if (cmd->fd_in != STDIN_FILENO)
//             {
//                 dup2(cmd->fd_in, STDIN_FILENO);
//                 close(cmd->fd_in);
//             }
//             if (cmd->fd_out != STDOUT_FILENO)
//             {
//                 dup2(cmd->fd_out, STDOUT_FILENO);
//                 close(cmd->fd_out);
//             }
// 			if (is_builtin(cmd->bin))
// 			{
// 				g_exit_num = handle_builtin(shell, cmd);
// 				exit(g_exit_num);
// 			}
// 			args = arg_nodes_to_arg_array(cmd);
// 			g_exit_num = execve(cmd->bin, args, shell->envp);
// 			//si e intenta ejecutar una carpeta tiene que emitir error 126
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
// 			if (cmd->fd_in != STDIN_FILENO)
// 				close(cmd->fd_in);
// 			if (cmd->fd_out != STDOUT_FILENO)
// 				close(cmd->fd_out);
// 		}
// 		cmd_node = cmd_node->next;
// 		i++;
// 	}
// 	while (waitpid(-1, &status, 0) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			g_exit_num = WEXITSTATUS(status);
// 	}
// }

static void	aux_pipex(t_cmd *cmd, t_shell *shell)
{
	char	**args;

	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (is_builtin(cmd->bin))
	{
		g_exit_num = handle_builtin(shell, cmd);
		exit(g_exit_num);
	}
	args = arg_nodes_to_arg_array(cmd);
	g_exit_num = execve(cmd->bin, args, shell->envp);
	print_error("execve");
}

static void	exit_status_transmisor(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_num = WEXITSTATUS(status);
	}
}

// void	close_fds(int i, t_shell *shell, t_cmd *cmd, int p[2])
// {
// 	int pipe_read;

// 	pipe_read = -1;
// 		if (i > 0)
// 		close(pipe_read);
// 	if (i < shell->cmd_count - 1)
// 	{
// 		close(p[WRITE_END]);
// 		pipe_read = p[READ_END];
// 	}
// 	if (cmd->fd_in != STDIN_FILENO)
// 		close(cmd->fd_in);
// 	if (cmd->fd_out != STDOUT_FILENO)
// 		close(cmd->fd_out);
// }
// void	duplicate_fds(int i, t_cmd *cmd, t_shell *shell, int p[2])
// {
// 	int	pipe_read;

// 	pipe_read = -1;
// 	if (i > 0)
// 	{
// 		dup2(pipe_read, cmd->fd_in);
// 		close(pipe_read);
// 	}
// 	if (i < shell->cmd_count - 1)
// 	{
// 		close(p[READ_END]);
// 		dup2(p[WRITE_END], cmd->fd_out);
// 		close(p[WRITE_END]);
// 	}
// }

void	ft_piped_exec(t_shell *shell)
{
	int		p[2];
	int		i;
	int		pid;
	int		pipe_read;
	t_node	*cmd_node;
	t_cmd	*cmd;

	i = 0;
	pipe_read = -1;
	cmd_node = shell->cmds;
	while (i < shell->cmd_count && cmd_node)
	{
		cmd = (t_cmd *)cmd_node->content;
		if (i < shell->cmd_count - 1 && pipe(p) == -1)
			print_error("pipe");
		pid = fork();
		if (pid == -1)
			print_error("fork");
		else if (pid == 0)
		{
			if (i > 0)
			{
				dup2(pipe_read, cmd->fd_in);
				close(pipe_read);
			}
			if (i < shell->cmd_count - 1)
			{
				close(p[READ_END]);
				dup2(p[WRITE_END], cmd->fd_out);
				close(p[WRITE_END]);
			}
			aux_pipex(cmd, shell);
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
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			if (cmd->fd_out != STDOUT_FILENO)
				close(cmd->fd_out);
		}
		cmd_node = cmd_node->next;
		i++;
	}
	exit_status_transmisor();
}
