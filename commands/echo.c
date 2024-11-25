/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/25 21:40:10 by saul.blanco      ###   ########.fr       */
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

//codigos de error comprobados

int	ft_echo(t_cmd *cmd)
{
	int		i;
	t_node	*arg_node;
	bool	new_line;
	
	i = 0;
	new_line = true;
	arg_node = cmd->args->next;
	while (arg_node && !ft_strncmp((char *) arg_node->content, "-n", 2))
	{
		new_line = false;
		arg_node = arg_node->next;
	}
	while (arg_node)
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
