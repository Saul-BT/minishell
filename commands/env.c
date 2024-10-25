/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 13:35:10 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_print_special(char *str)
// {
// 	size_t	len;

// 	len = ft_strlen(str);
// 	write(1, str, len);
// 	write(1, "\n", 1);
// }

// void	ft_env(t_shell *shell)
// {
// 	int		j;
// 	char	**env;

// 	env = shell->envp;
// 	j = 0;
// 	while (env[j])
// 	{
// 		ft_print_special(env[j]);
// 		j++;
// 	}
// }

void	ft_env(t_shell *shell)
{
	int		j;
	char	**env;

	env = shell->envp;
	j = 0;
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
}

