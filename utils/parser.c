/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:44:25 by sblanco-          #+#    #+#             */
/*   Updated: 2024/07/25 10:48:56 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_bin_paths(char **envp)
{
	char	**bin_paths;

	while (envp && *envp)
	{
		if (starts_with(*envp, "PATH="))
		{
			bin_paths = ft_split(*envp + 5, ':');
			return (bin_paths);
		}
		envp++;
	}
	return (NULL);
}

static char	*get_check_cmd(char *cmd, t_shell *cfg)
{
	if (access(cmd, F_OK) != 0 || !has_char(cmd, '/'))
	{
		printf("pipex: %s: command not found\n", cmd);
		cfg->exit_code = 127;
	}
	else if (access(cmd, X_OK) != 0)
	{
		printf("pipex: %s: %s\n", cmd, strerror(errno));
		cfg->exit_code = 126;
	}
	return (cmd);
}

char	*get_bin_path(char *cmd, char **bin_paths, t_shell *cfg)
{
	char	*temp;
	char	*bin_path;
	bool	is_cmd_path;

	bin_path = NULL;
	is_cmd_path = starts_with(cmd, "/") || starts_with(cmd, "./")
		|| starts_with(cmd, "../");
	while (bin_paths && *bin_paths)
	{
		if (!is_cmd_path)
		{
			temp = ft_strjoin("/", cmd);
			bin_path = ft_strjoin(*bin_paths, temp);
			free(temp);
		}
		if (bin_path && access(bin_path, F_OK) == 0)
		{
			free(cmd);
			return (bin_path);
		}
		free(bin_path);
		bin_path = NULL;
		bin_paths++;
	}
	return (get_check_cmd(cmd, cfg));
}

// TODO: Handle literal pipes instead argv, we need a
// custom "split" becase the pipe can have an arbitrary
// number of spaces around...
char	***get_cmds(t_shell *cfg, char **argv)
{
	int		i;
	char	**bin_paths;
	t_cmd	**cmds;
	char	**cmd_with_args;

	i = 0;
	cmds = malloc(cfg->cmd_count * sizeof(t_cmd *));
	if (!cmds)
		return (NULL);
	bin_paths = get_bin_paths(cfg->envp);
	while (i < cfg->cmd_count)
	{
		cmd_with_args = ft_split(argv[i], ' ');
		cfg->exit_code = 0;
		cmd_with_args[0] = get_bin_path(cmd_with_args[0], bin_paths, cfg);
		cmds[i]->bin = cmd_with_args[0];
		cmds[i]->args = cmd_with_args + sizeof(char *);
		i++;
	}
	free_strs(bin_paths);
	return (NULL);
}
