/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 21:55:36 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	aux_pipex(t_cmd *cmd, t_shell *shell)
{
	char	**args;

	if (is_builtin(cmd->bin))
	{
		shell->exit_code = handle_builtin(shell, cmd);
		exit(shell->exit_code);
	}
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
	args = arg_nodes_to_arg_array(cmd);
	shell->exit_code = execve(cmd->bin, args, shell->envp);
	if (shell->exit_code == -1)
		shell->exit_code = 127;
	exit(shell->exit_code);
}

static pid_t	execute_command(t_cmd *cmd, t_pipe_ctx *ctx, t_shell *shell)
{
	pid_t	pid;

	if (!cmd->bin)
		return (-1);
	if (ctx->cmd_index < ctx->shell->cmd_count - 1 && pipe(ctx->pipe) == -1)
		print_error("pipe", shell);
	pid = fork();
	if (pid == -1)
		print_error("fork", shell);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_non_interactive);
		setup_child_pipes(cmd, ctx);
		aux_pipex(cmd, ctx->shell);
	}
	else
		sig_ignore();
	if (ctx->cmd_index < ctx->shell->cmd_count - 1)
	{
		handle_parent_pipes(cmd, ctx);
	}
	return (pid);
}

void	ft_piped_exec(t_shell *shell)
{
	t_pipe_ctx	ctx;
	t_node		*cmd_node;
	pid_t		last;

	ctx.cmd_index = 0;
	ctx.pipe_read = -1;
	ctx.shell = shell;
	cmd_node = shell->cmds;
	while (ctx.cmd_index < shell->cmd_count && cmd_node)
	{
		last = execute_command((t_cmd *)cmd_node->content, &ctx, shell);
		cmd_node = cmd_node->next;
		ctx.cmd_index++;
	}
	if (ctx.pipe_read > 2)
		close(ctx.pipe_read);
	shell->exit_code = exit_status_transmisor(shell->cmd_count, last);
}
