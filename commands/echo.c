/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/06 20:47:43 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (!(arg[i] == '-'))
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	t_node	*arg_node;
	bool	new_line;

	i = 0;
	new_line = true;
	arg_node = cmd->args->next;
	while (arg_node && check_flag((char *) arg_node->content))
	{
		new_line = false;
		arg_node = arg_node->next;
	}
	// while (arg_node) 
	// {
	// 	if (i > 0)
	// 		printf(" ");
	// 	printf("%s", (char *)arg_node->content);
	// 	arg_node = arg_node->next;
	// 	i++;
	// }
	while (arg_node)
	{
		if (i > 0)
			ft_putchar_fd(' ', cmd->fd_out);
		ft_putstr_fd((char *)arg_node->content, cmd->fd_out);
		arg_node = arg_node->next;
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', cmd->fd_out);
	return (0);
}
