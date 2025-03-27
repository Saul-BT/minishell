/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:47:30 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/27 18:02:43 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	execute_command(t_cmd *cmd, t_pipe_ctx *ctx)
{
	pid_t	pid;

	if (ctx->cmd_index < ctx->shell->cmd_count - 1 && pipe(ctx->pipe) == -1)
		print_error("pipe");
	pid = fork();
	if (pid == -1)
		print_error("fork");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		setup_child_pipes(cmd, ctx);
		aux_pipex(cmd, ctx->shell);
	}
	// else if (ctx->cmd_index < ctx->shell->cmd_count - 1)
	// 	handle_parent_pipes(cmd, ctx);
	if (ctx->cmd_index < ctx->shell->cmd_count - 1)
		handle_parent_pipes(cmd, ctx);
}

void	ft_piped_exec(t_shell *shell)
{
	t_pipe_ctx	ctx;
	t_node		*cmd_node;

	ctx.cmd_index = 0;
	ctx.pipe_read = -1;
	ctx.shell = shell;
	cmd_node = shell->cmds;
	while (ctx.cmd_index < shell->cmd_count && cmd_node)
	{
		execute_command((t_cmd *)cmd_node->content, &ctx);
		cmd_node = cmd_node->next;
		ctx.cmd_index++;
	}
	if (ctx.pipe_read > 2)
		close(ctx.pipe_read);
	exit_status_transmisor();
}
