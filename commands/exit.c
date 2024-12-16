/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:37:07 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 21:20:00 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR MAX LONG LONG Y MIN LONG LONG

int	valid_exit(t_node *args, int arg_count)
{
	int	i;

	i = 0;
	if (!args || !args->next)
		return (0);
	while (((char *)args->next->content)[i])
	{
		if (!ft_isdigit(((char *)args->next->content)[i]))
			return (2);
		i++;
	}
	if (arg_count > 2)
		return (1);
	return (0);
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	error;


	error = valid_exit(cmd->args, cmd->arg_count);
	printf("exit\n");
	if (error == 1)
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	shell->exit_code = 1;
	if (error == 2)
	{
		printf("bash: exit: %s: numeric argument required\n", cmd->bin);
		return (2);
	}
	else if (cmd->args && cmd->args->next)
		return (ft_atoi((char *)cmd->args->next->content));
	return (0);
}
