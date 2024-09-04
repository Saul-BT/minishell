/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:00 by sblanco-          #+#    #+#             */
/*   Updated: 2024/09/04 19:27:53 by mmartine         ###   ########.fr       */
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
// void			handle_builtin(const char **cmd);
void			handle_builtin(t_shell *shell);
// void			ft_cd(const char **args);
void			ft_cd(t_shell *shell);
// void			ft_echo(const char **args);
void			ft_echo(t_shell *shell);
// void			ft_env(const char **args);
void			ft_env(t_shell *shell);
void			ft_exit(const char **args);
// void			ft_export(const char **args);
void			ft_export(t_shell *shell);
// void			ft_pwd(const char **args);
void			ft_pwd(t_shell *shell);
// void			ft_unset(const char **args);
void			ft_unset(t_shell *shell);

// UTILS
int				ft_strcmp(const char *s1, const char *s2);
const char		***get_cmds(t_shell *cfg, char **argv);
bool			starts_with(const char *str, const char *prefix);
void			free_strs(char **strs);
bool			has_char(const char *str, char c);
char			*ft_join(const char **strs);
char			**pipe_split(const char *str, int *cmd_count);
bool			is_quoted(char c);

//esta en export
char	**new_env(char **env, int n, int add, char *val);

//utils de bultins
char	*ft_get_env_val(t_shell *shell, char *var);
void	ft_set_env_val(t_shell *shell, char *var, char *mod);
void	free_env(char **env);
int		ft_get_env_pos(t_shell *shell, char *var);


#endif