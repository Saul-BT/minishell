/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:44:25 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/27 14:13:01 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_check_cmd(char *cmd, t_shell *cfg)
{

	//ELIMINAR ESTO
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
			free((void *)cmd);
			return (bin_path);
		}
		free(bin_path);
		bin_path = NULL;
		bin_paths++;
	}
	return (get_check_cmd(cmd, cfg));
}

t_node	*error_exit(t_shell *cfg, char **bin_paths, char **argv, t_cmd *cmd)
{
	// int	i;

	// i = 0;
	if (cfg->cmd_count == 1)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (cfg->cmd_count == 2)
	{
		free(cmd->args);
		printf("bash: syntax error near unexpected token `|'\n");
	}
	free(cmd);
	free_strs(bin_paths);
	free(argv);
	return (NULL);
}

t_node	*get_cmds(t_shell *cfg, char **argv)
{
	int		i;
	char	**bin_paths;
	t_node	*cmds;
	t_cmd	*cmd;

	i = 0;
	// TODO: Maybe need to check if there is a PATH before
	bin_paths = ft_split(getenv("PATH"), ':');
	cmds = NULL;
	while (i < cfg->cmd_count)
	{
		// printf("cmd count---%i---\n", cfg->cmd_count);
		// TODO: Add check for the returned value (it can be NULL)
		cmd = tokenize(argv[i], cfg);
		// printf("---argc: %i----\n",cmd->arg_count);
		free(argv[i]);
		//REVISAR SI ESTO ROMPE ALGO QUE NO SEAN ARGUMENTOS VACIOS
		// if (cmd->arg_count == 0)
		// 	return (error_exit(cfg, bin_paths, argv, cmd));
		cfg->exit_code = 0;
		if (!is_builtin(cmd->bin))
		{
			cmd->bin = get_bin_path(cmd->bin, bin_paths, cfg);
			cmd->args->content = cmd->bin;
		}
		ft_lstadd_back(&cmds, ft_lstnew(cmd));
		i++;
	}
	free_strs(bin_paths);
	free(argv);
	return (cmds);
}
