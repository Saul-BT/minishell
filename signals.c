/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:50:46 by mmartine          #+#    #+#             */
/*   Updated: 2024/10/07 19:22:11 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//padre
void	sig_manage(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		// g_exit_status = 1;
	}
	else if (signum == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
}

//hijos
// void	sig_manage(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		// g_exit_status = 0;
// 	}
// 	else if (signum == SIGQUIT)
// 		signal(SIGQUIT, SIG_IGN);
	
	
// }
