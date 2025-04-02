/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:00:43 by mmartine          #+#    #+#             */
/*   Updated: 2025/04/02 19:00:16 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	accesible_file(char	*filename, int access_mode)
{
	int	fd;

	g_exit_num = 1;
	if (access_mode != O_RDONLY)
	{
		fd = open(filename, O_DIRECTORY);
		if (fd >= 0)
		{
			close(fd);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filename, 2);
			return (ft_putstr_fd(": Is a directory\n", 2), false);
		}
	}
	fd = open(filename, access_mode, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		return (ft_putstr_fd(": Permission denied\n", 2), false);
	}
	else if (access(filename, F_OK) < 0)
	{
		close(fd);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), false);
	}
	close(fd);
	g_exit_num = 0;
	return (true);
}

size_t	ft_index_of_symbol(char *str)
{
	static char	*symbols = " <>;'\"";
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(symbols, str[i]))
			return (i);
		i++;
	}
	return ((size_t)-1);
}

char	*file_name_non_quoted(char *name)
{
	char	*non_q;

	if (name[0] == '"')
	{
		free(name);
		non_q = ft_strtrim(name, "\"");
	}
	else if (name[0] == '\'')
	{
		free(name);
		non_q = ft_strtrim(name, "'");
	}
	else
		return (name);
	return (non_q);
}

t_cmd	*init_tokenizer(size_t *len, char *expanded)
{
	t_cmd	*cmd;

	*len = ft_strlen(expanded);
	cmd = malloc(sizeof(t_cmd));
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	return (cmd);
}