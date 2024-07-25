/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:00:46 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 13:38:13 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**pipe_split(const char *str)
{
	size_t i;
	char	*trimmed;
	char	**result;

	i = 0;
	result = ft_split(str, '|');
	while (result[i])
	{
		trimmed = ft_strtrim(result[i], " \t\n\v\f\r");
		free(result[i]);
		result[i] = trimmed;
		i++;
	}
	return (result);
}
