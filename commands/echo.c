/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/19 18:48:00 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR -nnnnnnnn y -n -n -n -n

int	ft_echo(t_shell *shell, int argnum)
{
	const char	**args;
	char		*joined;

	args = shell->cmds[argnum];
	if (!*args[1])
	{
		printf("\n");
		return (0);
	}
	if (args && *args && !ft_strncmp(args[1], "-n", 3))
	{
		joined = ft_join(args + 2);
		printf("%s", joined);
		free(joined);
		return (0);
	}
	joined = ft_join(args + 1);
	printf("%s\n", joined);
	free(joined);
	return (0);
}
