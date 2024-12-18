/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/28 10:24:59 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*curr_dir;
	int		ret;

	(void)shell;
	ret = 1;
	curr_dir = getcwd(NULL, 0);
	if (curr_dir)
	{
		printf("%s\n", curr_dir);
		ret = 0;
	}
	free(curr_dir);
	return (ret);
}
