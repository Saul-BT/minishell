/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:50:46 by mmartine          #+#    #+#             */
/*   Updated: 2025/03/27 19:48:00 by mmartine         ###   ########.fr       */
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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_num = 130;
	}
}

void	sig_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		// write(1, "\n", 1);
		rl_replace_line("\n", 1);
		rl_on_new_line();
		g_exit_num = 130;
	}
	else if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_DFL);
		write(1, "\n", 1);
		g_exit_num = 131;
	}
}

void	sig_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		g_exit_num = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\r");
	}
	else if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		rl_replace_line("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_num = 0;
	}
}

void	sig_manage(t_shell *shell, int interactive)
{
	if (interactive == 1)
	{
		// write_signals(shell, 1);
		signal(SIGINT, sig_interactive);
		signal(SIGQUIT, sig_interactive);
		// write_signals(shell, 0);

	}
	else if (interactive == 2)
	{
		// write_signals(shell, 1);
		write_signals(shell, 0);
		signal(SIGINT, sig_here_doc);
		signal(SIGQUIT, sig_here_doc);
	}
	else
	{
		// write_signals(shell, 0);
		signal(SIGINT, sig_non_interactive);
		signal(SIGQUIT, sig_non_interactive);
		// write_signals(shell, 1);

	}
}

