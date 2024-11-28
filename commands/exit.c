/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:37:07 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/19 18:46:05 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR MAX LONG LONG Y MIN LONG LONG

int	valid_exit(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			return (2);
		i++;
	}
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

int	ft_exit(t_shell *shell, int argnum)
{
	int	error;


	error = valid_exit((char **)shell->cmds[argnum]);
	printf("exit\n");
	if (error == 1)
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	shell->exit_code = 1;
	if (error == 2)
	{
		printf("bash: exit: %s: numeric argument required\n",
			shell->cmds[argnum][1]);
		return (2);
	}
	else if (shell->cmds[argnum][1])
		return (ft_atoi(shell->cmds[argnum][1]));
	return (0);
}
