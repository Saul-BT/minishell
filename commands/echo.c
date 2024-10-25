/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 13:55:47 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_echo(const char **args)
// {
// 	if (args && *args && !ft_strcmp(*args, "-n\0")) {
// 		printf("%s", ft_join(args + 1));
// 		return;
// 	}
// 	printf("%s\n", ft_join(args));
// }

// TODO: Remove the tricky ft_join

void	ft_echo(t_shell *shell, int argnum)
{
	const char	**args;
	char *joined;
	
	// printf("en echo:\n---argnum = %i\n+++%s\n\n",argnum, shell->cmds[argnum][1]);
	args = shell->cmds[argnum];
	if (args && *args && !ft_strncmp(*args, "-n", 2))
	{
		joined = ft_join(args + 2);
		printf("%s", joined);
		free(joined);
		return ;
	}
	joined = ft_join(args + 1);
	printf("%s\n", joined);
	free(joined);
}
