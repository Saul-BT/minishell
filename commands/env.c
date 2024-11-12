/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/30 18:47:17 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//codigos de error comprobados

int	ft_env(t_shell *shell)
{
	int		j;
	char	**env;

	env = shell->envp;
	j = 0;
	if (!env)
		return (1);
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
	return (0);
}

