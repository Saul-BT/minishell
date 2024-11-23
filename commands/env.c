/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/23 12:47:01 by saul.blanco      ###   ########.fr       */
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

