/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 21:06:31 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR -nnnnnnnn y -n -n -n -n

int	ft_echo(t_cmd *cmd)
{
	int		i;
	t_node	*arg_node;
	bool	new_line;
	
	i = 0;
	arg_node = cmd->args;
	if (!arg_node->next)
	{
		printf("\n");
		return (0);
	}
	new_line = ft_strncmp((char *) arg_node->next->content, "-n", 2);
	if (new_line)
		arg_node = arg_node->next;
	while (i < cmd->arg_count && arg_node)
	{
		if (i > 0)
			printf(" ");
		printf("%s", (char *)arg_node->content);
		arg_node = arg_node->next;
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
