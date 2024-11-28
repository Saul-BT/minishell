/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 20:48:58 by saul.blanco      ###   ########.fr       */
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
