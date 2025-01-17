/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/17 02:24:13 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_oldpwd(t_shell *shell)
{
	return (chdir(ft_get_env_val(shell, "OLDPWD")));
}

int	nonerror_cd(char *oldpath, char *nd_arg, t_shell *shell)
{
	char	*curr_loc;
	char	*aux;

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
	free(oldpath);
	free(curr_loc);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	*oldpath;
	char	*nd_arg;

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
		return (nonerror_cd(oldpath, nd_arg, shell));
	else
	{
		printf("bash: cd: %s: No such file or directory\n",
			(char *)cmd->args->next->content);
		if (oldpath)
			free(oldpath);
		return (1);
	}
}
