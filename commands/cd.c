/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/02 23:36:49 by sblanco-         ###   ########.fr       */
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
		printf("cd: error retrieving current directory: getcwd: cannot access"
			"parent directories: No such file or directory\n");
		aux = ft_strjoin(oldpath, "/");
		curr_loc = ft_strjoin(aux, nd_arg);
		free(aux);
	}
	ft_set_env_val(shell, "OLDPWD", oldpath,
		ft_get_env_pos(shell->envp, "OLDPWD"));
	ft_set_env_val(shell, "PWD", curr_loc,
		ft_get_env_pos(shell->envp, "PWD"));
	if (oldpath)
		free(oldpath);
	free(curr_loc);
	return (0);
}

int	if_non_next(t_cmd *cmd, char *oldpath)
{
	if (cmd->args->next)
		return (0);
	free(oldpath);
	return (1);
}

int	ret_error(t_cmd *cmd, char *oldpath)
{
	printf("bash: cd: %s: No such file or directory\n",
		(char *)cmd->args->next->content);
	if (oldpath)
		free(oldpath);
	return (1);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	*oldpath;
	t_node	*nd_arg;

	oldpath = getcwd(NULL, 0);
	if (!oldpath)
		oldpath = ft_strdup(ft_get_env_val(shell, "PWD"));
	// TODO: este if de abajo impide que se gestione "cd" sin args correctamente
	if (if_non_next(cmd, oldpath))
		return (2);
	nd_arg = cmd->args->next;
	if (!nd_arg)
		ret = chdir(ft_get_env_val(shell, "HOME"));
	else if (nd_arg->content && ((char *) nd_arg->content)[0] == '-')
		ret = ft_cd_oldpwd(shell);
	else
		ret = chdir((char *) nd_arg->content);
	if (!ret)
		return (nonerror_cd(oldpath, (char *) nd_arg->content, shell));
	else
		return (ret_error(cmd, oldpath));
}
