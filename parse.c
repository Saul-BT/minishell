/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:04:41 by mmartine          #+#    #+#             */
/*   Updated: 2024/04/24 20:16:29 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_shell **args)
{
	t_shell	*next_arg;
	char	**splitarg;

	splitarg = ft_split(input, ' ');
	if (!*args)
	
	return ;
}
