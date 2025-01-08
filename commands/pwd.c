/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/08 19:31:59 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*curr_dir;
	int		ret;

	ret = 1;
	curr_dir = getcwd(NULL, 0);
	if (curr_dir)
		ret = 0;
	else
		curr_dir = ft_get_env_val(shell, "PWD");
	ft_putstr_fd(curr_dir, cmd->fd_out);
	ft_putchar_fd('\n', cmd->fd_out);
	if (!ret)
		free(curr_dir);
	return (ret);
}
