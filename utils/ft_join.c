/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:20:19 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 19:15:37 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join(const char **strs)
{
	size_t i;
	char *tmp;
	char *result;

	if (!strs || !*strs || !**strs || **strs == '\0')
		return ("");
	i = 1;
	result = ft_strdup(strs[0]);
	while (strs[i])
	{
		tmp = result;
		result = ft_strjoin(result, " ");
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, strs[i]);
		free(tmp);
		i++;
	}
	return (result);
}