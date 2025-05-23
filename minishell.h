/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:00 by sblanco-          #+#    #+#             */
/*   Updated: 2025/04/03 22:55:00 by mmartine         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
// # include <asm/termbits.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_quoted
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NOPE,
}			t_quoted;

typedef struct s_parsed_token
{
	char	*parsed;
	int		skip;
}			t_parsed_token;

typedef struct s_cmd
{
	char	*bin;
	t_node	*args;
	int		arg_count;
	int		fd_in;
	int		fd_out;
}			t_cmd;

typedef struct s_shell
{
	int		interactive;
	char	**envp;
	t_node	*cmds;
	int		cmd_count;
	int		exit_code;
	int		exit_loop;
}			t_shell;

typedef struct s_pipe_ctx
{
	int		pipe[2];
	int		pipe_read;
	int		cmd_index;
	t_shell	*shell;
}			t_pipe_ctx;

extern int	g_exit_num;

//MAIN
void			check_shlvl(int n, t_shell *shell);
t_shell			*initshell(char **env);

// BUILTINS
bool			is_builtin(const char *cmd);
int				handle_builtin(t_shell *shell, t_cmd *cmd);
int				ft_cd(t_cmd *cmd, t_shell *shell);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_cmd *cmd, t_shell *shell);
int				ft_exit(t_shell *shell, t_cmd *cmd);
int				ft_export(t_cmd *cmd, t_shell *shell);
int				ft_pwd(t_cmd *cmd, t_shell *shell);
int				ft_unset(t_cmd *cmd, t_shell *shell);
void			print_sorted_env(t_shell *shell, char **env, int n, t_cmd *cmd);
char			**new_env(char **env, int n, int add, char *val);

// UTILS
bool			is_quoted(char c);
bool			is_symbol(char c, char symbol);
bool			is_word_boundary(char a, char b);
void			close_quote(void);
int				count_pipes(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
t_node			*get_cmds(t_shell *cfg, char **argv);
bool			starts_with(const char *str, const char *prefix);
void			free_strs(char **strs);
void			free_cmds(t_node *cmds);
bool			has_char(const char *str, char c);
char			**pipe_split(const char *str, int *cmd_count);
bool			is_quoted(char c);
void			close_quote(void);
void			print_error(char *msg, t_shell *shell);
bool			is_valid_var_start_char(char c);
bool			is_valid_var_char(char c);
bool			accesible_file(char	*filename, int access_mode, t_shell *shell);

// esta en export
char			**new_env(char **env, int n, int add, char *val);

// EXPANSOR
char			**expand(t_shell *shell, char **args);
char			*expand_super(char *str, t_shell *cfg);

// utils de bultins
char			*ft_get_env_val(t_shell *shell, char *var);
void			ft_set_env_val(t_shell *shell, char *var, char *mod, int pos);
void			free_env(char **env);
int				ft_get_env_pos(char **env, char *var);
char			*ft_envformat_converter(char *var);
char			*ft_get_env_name(char *arg);

// PIPES
void			ft_piped_exec(t_shell *shell);

// PIPES UTILS
char			**arg_nodes_to_arg_array(t_cmd *cmd);
int				exit_status_transmisor(int arg_num, pid_t last);
void			setup_child_pipes(t_cmd *cmd, t_pipe_ctx *ctx);
void			handle_parent_pipes(t_cmd *cmd, t_pipe_ctx *ctx);

//	SIGNALS
void			sig_manage(t_shell *shell, int interactive);
void			sig_interactive(int signum);
void			sig_ignore(void);
void			sig_non_interactive(int signum);

// TOKENIZER
t_cmd			*tokenize(char *cmd_line, t_shell *cfg, bool first_parsed);
t_cmd			*init_tokenizer(size_t *len, char *expanded);
char			*file_name_non_quoted(char *name);
size_t			ft_index_of_symbol(char *str);

//REDIRS
t_parsed_token	*handle_in_redirect(char *token, t_cmd *cmd, t_shell *cfg);
t_parsed_token	*handle_heredoc(char *token, t_cmd *cmd, t_shell *cfg);
t_parsed_token	*handle_out_redirect(char *token, t_cmd *cmd, t_shell *cfg);
t_parsed_token	*handle_other(char *token, t_shell *cfg);
t_parsed_token	*handle_quote(char *token, char quote, t_shell *cfg);
void			write_in_heredoc(char *line, t_shell *cfg, int *pipe_fd);
void			manage_heredoc_pipes(int pipe_fd[2], t_cmd *cmd);
void			clean_heredoc_error(t_cmd *cmd, t_shell *shell);

#endif