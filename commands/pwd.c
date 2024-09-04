/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/03 17:18:04 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*curr_dir;

	(void)shell;
	curr_dir = getcwd(NULL, 0);
	if (curr_dir)
		printf("%s\n", curr_dir);
	free(curr_dir);
}
