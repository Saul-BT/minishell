/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/29 18:48:05 by mmartine         ###   ########.fr       */
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
	char	*curr_loc;
	char	*aux;
	
	oldpath = getcwd(NULL, 0);
	if (!oldpath)
		oldpath = ft_get_env_val(shell, "PWD");
	nd_arg = (char *) cmd->args->next->content;
	if (!nd_arg)
		ret = chdir(ft_get_env_val(shell, "HOME"));
	else if (nd_arg[0] == '-')
		ret = ft_cd_oldpwd(shell);
	else
		ret = chdir(nd_arg);
	if (!ret)
	{
		curr_loc = getcwd(NULL, 0);
		if (!curr_loc)
		{
			aux = ft_strjoin(oldpath, "/");
			curr_loc = ft_strjoin(aux, nd_arg);
			free(aux);
		}
		ft_set_env_val(shell, "OLDPWD", oldpath,
			ft_get_env_pos(shell->envp, "OLDPWD"));
		ft_set_env_val(shell, "PWD", curr_loc,
			ft_get_env_pos(shell->envp, "PWD"));
		return (0);
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n",
			(char *)cmd->args->next->content);
		return (1);	
	}
	if (oldpath)
		free(oldpath);
}
