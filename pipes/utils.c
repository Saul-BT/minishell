/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:57 by saul.blanco       #+#    #+#             */
/*   Updated: 2025/03/30 17:28:09 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arg_nodes_to_arg_array(t_cmd *cmd)
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

void	exit_status_transmisor(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_num = WEXITSTATUS(status);
	}
}

void	setup_child_pipes(t_cmd *cmd, t_pipe_ctx *ctx)
{
	if (ctx->cmd_index > 0)
	{
		dup2(ctx->pipe_read, STDIN_FILENO);
		close(ctx->pipe_read);
	}
	if (ctx->cmd_index < ctx->shell->cmd_count - 1)
	{
		close(ctx->pipe[READ_END]);
		dup2(ctx->pipe[WRITE_END], STDOUT_FILENO);
		close(ctx->pipe[WRITE_END]);
	}
	if (is_builtin(cmd->bin))
		return;
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
}

void	handle_parent_pipes(t_cmd *cmd, t_pipe_ctx *ctx)
{
	if (ctx->cmd_index > 0)
		close(ctx->pipe_read);
	ctx->pipe_read = ctx->pipe[READ_END];
	close(ctx->pipe[WRITE_END]);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}
