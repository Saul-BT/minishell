/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 21:06:04 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_oldpwd(t_shell *shell)
{
	return (chdir(ft_get_env_val(shell, "OLDPWD")));
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	*oldpath;
	char	*nd_arg;

	oldpath = getcwd(NULL, 0);
	nd_arg = (char *) cmd->args->next->content;
	// printf("en cd:\n---argnum = %i\n+++%s\n\n",argnum, shell->cmds[argnum][1]);
	if (!nd_arg)
		ret = chdir(ft_get_env_val(shell, "HOME"));
	else if (nd_arg[0] == '-')
		ret = ft_cd_oldpwd(shell);
	else
		ret = chdir(nd_arg);
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
