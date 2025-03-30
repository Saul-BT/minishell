/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/03/30 21:52:48 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_new_val(char *var)
{
	int		i;
	char	*newval;
	int		size;

	i = 0;
	size = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (NULL);
	i++;
	while (var[i + size])
		size++;
	newval = ft_calloc(1, size + 1);
	size = 0;
	while (var[i + size])
	{
		newval[size] = var[i + size];
		size++;
	}
	return (newval);
}

bool	is_valid_export_var(char *str)
{
	if (!str || !*str)
		return (false);
	if (!is_valid_var_start_char(*str++))
		return (false);
	while (*str && *str != '=' && is_valid_var_char(*str))
		str++;
	return (*str == '=');
}

int	add_val(char *arg_val, t_shell *shell)
{
	char	*newval;

	if (!is_valid_export_var(arg_val))
	{
		printf("minishell: export: %s : not a valid identifier\n", arg_val);
		return (1);
	}
	else if (ft_get_env_pos(shell->envp, arg_val) >= 0)
	{
		newval = get_new_val(arg_val);
		ft_set_env_val(shell, arg_val, newval, ft_get_env_pos(shell->envp,
				arg_val));
		if (newval)
			free(newval);
		return (-1);
	}
	return (0);
}

int	modifyenv(t_shell *shell, t_node *arg, int n)
{
	char	**act_env;
	int		ret;
	t_node	*arg_node;
	char	*arg_val;

	arg_node = arg;
	ret = 0;
	while (arg_node)
	{
		arg_val = (char *)arg_node->content;
		ret = add_val(arg_val, shell);
		if (ret)
		{
			arg_node = arg_node->next;
			continue ;
		}
		act_env = new_env(shell->envp, n++, 1, (arg_val));
		free_env(shell->envp);
		shell->envp = act_env;
		arg_node = arg_node->next;
	}
	if (ret == 1)
		return (ret);
	return (0);
}

int	ft_export(t_cmd *cmd, t_shell *shell)
{
	char	**env_cpy;
	int		n;
	t_node	*arg_node;

	n = 0;
	if (!shell->envp)
		return (1);
	arg_node = cmd->args->next;
	if (arg_node && arg_node->content && ((char *)arg_node->content)[0] == '-')
	{
		printf("minishell: export: %s: invalid option\n", (char *)arg_node->content);
		return (2);
	}
	while (shell->envp[n])
		n++;
	if (arg_node == NULL)
	{
		env_cpy = new_env(shell->envp, n, 0, NULL);
		print_sorted_env(shell, env_cpy, n, cmd);
		free_env(env_cpy);
	}
	else
		return (modifyenv(shell, arg_node, n));
	return (0);
}
