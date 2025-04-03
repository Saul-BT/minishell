/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:07:20 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 21:54:13 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//el execve devuelve -1 en caso de error asii que lo sustituimos por 127.

void	print_error(char *msg, t_shell *shell)
{
	perror(msg);
	exit(shell->exit_code);
}
