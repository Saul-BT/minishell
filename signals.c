/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:50:46 by mmartine          #+#    #+#             */
/*   Updated: 2024/12/16 20:48:44 by saul.blanco      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_signals(t_shell *shell, int write_signal)
{
	struct termios	termios_p;

	(void)shell;
	if (tcgetattr(STDIN_FILENO, &termios_p) != 0)
		exit(1);
	if (write_signal)
		termios_p.c_lflag &= ~ECHOCTL;
	else
		termios_p.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &termios_p) != 0)
		exit(1);
}

void	sig_interactive(int signum)
{
	if (signum == SIGINT)
	{
		printf("> ^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_num = 130;
	}
	else if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_num = 0;
	}
}

void	sig_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_exit_num = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		g_exit_num = 131;
	}
}

void	sig_manage(t_shell *shell, int interactive)
{
	if (interactive)
	{
		write_signals(shell, 1);
		signal(SIGINT, sig_interactive);
		signal(SIGQUIT, sig_interactive);
	}
	else
	{
		write_signals(shell, 0);
		signal(SIGINT, sig_non_interactive);
		signal(SIGQUIT, sig_non_interactive);
	}
}

