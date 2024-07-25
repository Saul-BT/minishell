/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 19:13:01 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(const char **args)
{
	if (args && *args && !ft_strcmp(*args, "-n\0")) {
		printf("%s", ft_join(args + 1));
		return;
	}
	printf("%s\n", ft_join(args));
}
