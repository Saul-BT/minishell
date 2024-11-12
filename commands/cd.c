/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/28 10:19:18 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_oldpwd(t_shell *shell)
{
	return (chdir(ft_get_env_val(shell, "OLDPWD")));
}

int	ft_cd(t_shell *shell, int argnum)
{
	int		ret;
	char	*oldpath;

	oldpath = getcwd(NULL, 0);
	if (!shell->cmds[argnum][1])
		ret = chdir(ft_get_env_val(shell, "HOME"));
	else if (shell->cmds[argnum][1][0] == '-')
		ret = ft_cd_oldpwd(shell);
	else
		ret = chdir(shell->cmds[argnum][1]);
	if (!ret)
	{
		ft_set_env_val(shell, "OLDPWD", oldpath,
			ft_get_env_pos(shell->envp, "OLDPWD"));
		return (0);
	}
	else
	{
		printf("el cd ha ido mal(MENSAJE DE EJEMPLO)\n");
		return (1);	
	}
	if (oldpath)
		free(oldpath);
}
