/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:00 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/22 18:34:53 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// int	g_exit_num;

typedef enum e_quoted
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NOPE,
}				t_quoted;

typedef struct s_shell
{
	int			interactive;
	char		**envp;
	const char	***cmds;
	int			cmd_count;
	int			exit_code;
}				t_shell;

// BUILTINS
bool			is_builtin(const char *cmd);
void			handle_builtin(t_shell *shell, int argnum);
void			ft_cd(t_shell *shell, int argnum);
void			ft_echo(t_shell *shell, int argnum);
void			ft_env(t_shell *shell);
void			ft_exit(t_shell *shell);
void			ft_export(t_shell *shell, int argnum);
void			ft_pwd(t_shell *shell);
void			ft_unset(t_shell *shell, int argnum);

// UTILS
int				ft_strcmp(const char *s1, const char *s2);
const char		***get_cmds(t_shell *cfg, char **argv);
bool			starts_with(const char *str, const char *prefix);
void			free_strs(char **strs);
void			free_cmds(char ***cmds, int cmd_count);
bool			has_char(const char *str, char c);
char			*ft_join(const char **strs);
char			**pipe_split(const char *str, int *cmd_count);
bool			is_quoted(char c);
void			close_quote(void);
void			print_error(char *msg);

// esta en export
char			**new_env(char **env, int n, int add, char *val);

// utils de bultins
char			*ft_get_env_val(t_shell *shell, char *var);
void			ft_set_env_val(t_shell *shell, char *var, char *mod, int pos);
void			free_env(char **env);
int				ft_get_env_pos(char **env, char *var);
char			*ft_envformat_converter(char *var);
char			*ft_get_env_name(char *arg);

// PIPES
void			ft_piped_exec(t_shell *shell);

//	SIGNALS
void			sig_manage(int signum);


#endif