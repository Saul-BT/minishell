/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/29 18:55:04 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*curr_dir;
	int		ret;

	ret = 1;
	curr_dir = getcwd(NULL, 0);
	if (curr_dir)
		ret = 0;
	else
		curr_dir = ft_get_env_val(shell, "PWD");
	printf("%s\n", curr_dir);
	if (!ret)
		free(curr_dir);
	return (ret);
}
