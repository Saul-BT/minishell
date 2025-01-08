/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2025/01/06 21:24:30 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Ahora mismo se emplea shell.cmds[0] pues es el unico comando, habra que cambiar esa entrada y ajustar todo
//a que la entrada sea directamente el comando export con sus argumentos, pues hay dos casos:
// EXPORT SIN ARGUMENTOS: imprime la lista ordenada. Si luego usamos comando "env" debe imprimirse sin ordenar
//por lo que se hace una copia que luego se destruye
//EXPORT CON ARGUMENTOS: tiene tres casos.
//Caso 1: argumentos neuvos a los que no se asigna valor, se genera una copia de env con una nueva var que sustituye al env anterior
//Caso 2: argumentos nuevos con un igual (hay que mirar formato). Se genera un env con una nueva var tal que: hola="mundo"
//Caso 3: argumentos existentes a los que se les asigna un nuevo valor. Hay que chekear a la hora de introducir una nueva var si es que esta existe.

void	print_sorted_env(t_shell *shell, char **env, int n, t_cmd *cmd)
{
	int			sorted;
	char		*aux;
	int			i;

	sorted = 0;
	while (!sorted)
	{
		i = -1;
		sorted = 1;
		while (++i + 1 < n)
		{
			if (ft_strcmp((const char *)env[i], (const char *)env[i + 1]) > 0)
			{
				sorted = 0;
				aux = env[i];
				env[i] = env[i + 1];
				env[i + 1] = aux;
			}
		}
	}
	i = -1;
	while (env[++i])
	{
		aux = ft_get_env_name(env[i]);
		ft_putstr_fd("declare -x ", cmd->fd_out);
		ft_putstr_fd(aux, cmd->fd_out);
		ft_putstr_fd("=\"", cmd->fd_out);
		ft_putstr_fd(ft_get_env_val(shell, aux), cmd->fd_out);
		ft_putstr_fd("\"\n", cmd->fd_out);
		// printf("declare -x %s=\"%s\"\n", aux, ft_get_env_val(shell, aux));
		free(aux);
	}
}


char	**new_env(char **env, int n, int add, char *val)
{
	char	**cpy;
	int		i;

	i = -1;
	if (add && val)
	{
		cpy = malloc(sizeof(char *) * (n + 2));
		cpy[n + 1] = NULL;
		cpy[n] = ft_strdup(val);
	}
	else
	{
		cpy = malloc(sizeof(char *) * (n + 1));
		cpy[n] = NULL;
	}
	while (++i < n)
		cpy[i] = ft_strdup(env[i]);
	return (cpy);
}

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

int	modifyenv(t_shell *shell, t_node *arg, int n)
{
	char	**act_env;
	char	*newval;
	int		ret;
	t_node	*arg_node;
	char	*arg_val;

	arg_node = arg;
	ret = 0;
	while (arg_node)
	{
		arg_val = (char *) arg_node->content;
		if (arg_val[0] == '=' || ft_isdigit(arg_val[0]))
		{
			printf("bash: export: %s : not a valid identifier\n", arg_val);
			ret = 1;
			continue ;
		}
		else if (ft_get_env_pos(shell->envp, arg_val) >= 0)
		{
			newval = get_new_val(arg_val);
			ft_set_env_val(shell, arg_val, get_new_val(arg_val),
				ft_get_env_pos(shell->envp, arg_val));
			if (newval)
				free(newval);
			continue ;
		}
		act_env = new_env(shell->envp, n++, 1, (arg_val));
		free(shell->envp);
		shell->envp = act_env;
		arg_node = arg_node->next;
	}
	return (ret);
}


int	ft_export(t_cmd *cmd, t_shell *shell)
{
	char	**env_cpy;
	int		n;
	t_node	*nd_arg_node;

	n = 0;
	if (!shell->envp)
		return (1);
	nd_arg_node = cmd->args->next;
	if (nd_arg_node && nd_arg_node->content && ((char *)nd_arg_node->content)[0] == '-')
	{
		printf("bash: export: %s: invalid option\n", (char *)nd_arg_node->content);
		return (2);
	}
	while (shell->envp[n])
		n++;
	if (nd_arg_node == NULL)
	{
		env_cpy = new_env(shell->envp, n, 0, NULL);
		print_sorted_env(shell, env_cpy, n, cmd);
		free_env(env_cpy);
	}
	else
	{
		return (modifyenv(shell, nd_arg_node, n));
	}
	return (0);
}
