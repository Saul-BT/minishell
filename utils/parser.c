/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:44:25 by sblanco-          #+#    #+#             */
/*   Updated: 2024/10/23 18:15:07 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static const char	*get_check_cmd(const char *cmd, t_shell *cfg)
{
	if (is_builtin(cmd))
		return (cmd);
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

const char	*get_bin_path(const char *cmd, char **bin_paths, t_shell *cfg)
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
			free((void *)cmd);
			return (bin_path);
		}
		free(bin_path);
		bin_path = NULL;
		bin_paths++;
	}
	return (get_check_cmd(cmd, cfg));
}

const char	***get_cmds(t_shell *cfg, char **argv)
{
	int			i;
	char		**bin_paths;
	const char	***cmds;
	const char	**cmd_with_args;

	i = 0;
	cmds = malloc(cfg->cmd_count * sizeof(char **));
	// TODO: Maybe need to check if there is a PATH before
	bin_paths = ft_split(getenv("PATH"), ':');
	while (i < cfg->cmd_count)
	{
		// TODO: Add check for the returned value (it can be NULL)
		cmd_with_args = (const char **)ft_split(argv[i], ' ');
		free(argv[i]);
		cfg->exit_code = 0;
		// printmat((char **)cmd_with_args);
		cmd_with_args[0] = get_bin_path(cmd_with_args[0], bin_paths, cfg);
		cmds[i] = (const char **)expand(cfg, (char **)cmd_with_args);
		// cmds[i] = cmd_with_args;
		i++;
	}
	free_strs(bin_paths);
	free(argv);
	return (cmds);
}
