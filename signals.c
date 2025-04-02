/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:50:46 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/02 20:28:03 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_interactive(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_num = 130;
	}
}

void	sig_non_interactive(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_num = 130;
}

void	sig_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		g_exit_num = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\r");
	}
}

void	sig_manage(t_shell *shell, int interactive)
{
	(void)shell;
	if (interactive == 1)
		signal(SIGINT, sig_interactive);
	else if (interactive == 2)
		signal(SIGINT, sig_here_doc);
	else
		signal(SIGINT, sig_non_interactive);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
