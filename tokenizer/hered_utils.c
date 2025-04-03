/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hered_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:39:27 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 22:54:46 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_heredoc_pipes(int pipe_fd[2], t_cmd *cmd)
{
	close(pipe_fd[1]);
	if (cmd->fd_in > 1)
		close(cmd->fd_in);
	cmd->fd_in = pipe_fd[0];
}

void	clean_heredoc_error(t_cmd *cmd, t_shell *shell)
{
	printf("minishell: syntax error near unexpected token `<<'\n");
	cmd->bin = NULL;
	shell->exit_code = 2;
}

void	write_in_heredoc(char *line, t_shell *cfg, int *pipe_fd)
{
	char	*aux;

	aux = line;
	line = expand_super(aux, cfg);
	free(aux);
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	free(line);
}
