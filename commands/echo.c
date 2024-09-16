/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/15 09:58:20 by sblanco-         ###   ########.fr       */
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
void	ft_echo(t_shell *shell)
{
	const char	**args;
	char *joined;

	args = shell->cmds[0];
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
