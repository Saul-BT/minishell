/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:00 by sblanco-          #+#    #+#             */
/*   Updated: 2024/04/15 08:20:44 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**envp;
	t_cmd	**cmds;
	int		cmd_count;
	int		exit_code;
}	t_shell;

typedef struct s_cmd 
{
	char	*bin;
	char	**args;
}	t_cmd;

// BUILTINS
void	handle_builtin(t_shell *shell);
void	ft_cd(t_shell *shell);
void	ft_echo(t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_exit(t_shell *shell);
void	ft_export(t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_unset(t_shell *shell);

// UTILS
int		ft_strcmp(const char *s1, const char *s2);
char	***get_cmds(t_shell *cfg, char **argv);

#endif