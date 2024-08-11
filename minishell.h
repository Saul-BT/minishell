/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:00 by sblanco-          #+#    #+#             */
/*   Updated: 2024/08/10 20:33:49 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_quoted
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NOPE,
}				t_quoted;

typedef struct s_shell
{
	char		**envp;
	const char	***cmds;
	int			cmd_count;
	int			exit_code;
}				t_shell;

// BUILTINS
void			handle_builtin(const char **cmd);
void			ft_cd(const char **args);
void			ft_echo(const char **args);
void			ft_env(const char **args);
void			ft_exit(const char **args);
void			ft_export(const char **args);
void			ft_pwd(const char **args);
void			ft_unset(const char **args);

// UTILS
int				ft_strcmp(const char *s1, const char *s2);
const char		***get_cmds(t_shell *cfg, char **argv);
bool			starts_with(const char *str, const char *prefix);
void			free_strs(char **strs);
bool			has_char(const char *str, char c);
char			*ft_join(const char **strs);
char			**pipe_split(const char *str, int *cmd_count);
bool			is_quoted(char c);

#endif