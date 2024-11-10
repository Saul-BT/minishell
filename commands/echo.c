/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/12/16 21:04:51 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//GESTIONAR -nnnnnnnn y -n -n -n -n

int	ft_echo(t_cmd *cmd)
{
	int		i;
	t_node	*arg_node;
	char	*nd_arg;
	bool	new_line;
	
	i = 0;
	arg_node = cmd->args;
	nd_arg = (char *) arg_node->next->content;
	new_line = ft_strncmp(nd_arg, "-n", 2);
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
