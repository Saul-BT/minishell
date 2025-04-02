/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:37:07 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/02 18:25:17 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR MAX LONG LONG Y MIN LONG LONG

static int	valid_exit(t_node *args, int arg_count)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (!args || !args->next)
		return (0);
	if (((char *)args->next->content)[i] == '-')
		i++;
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

static int	get_error_var_val(bool *jump, t_cmd *cmd)
{
	*jump = false;
	if (cmd->args->next && !ft_strncmp((char *)cmd->args->next->content, "--",
			ft_strlen((char *)cmd->args->next->content)))
	{
		*jump = true;
		return (valid_exit(cmd->args->next, cmd->arg_count - 1));
	}
	else
		return (valid_exit(cmd->args, cmd->arg_count));
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int		error;
	bool	jump;

	error = get_error_var_val(&jump, cmd);
	if (error == 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	shell->exit_code = -1;
	if (error == 2)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->bin);
		return (2);
	}
	else if (cmd->args && cmd->args->next)
	{
		if (jump && cmd->args->next->next)
			return (ft_atoi((char *)cmd->args->next->next->content));
		return (ft_atoi((char *)cmd->args->next->content));
	}
	return (0);
}
