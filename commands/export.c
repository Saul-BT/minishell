/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul.blanco <sblanco-@student.42madrid.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/11/23 12:47:06 by saul.blanco      ###   ########.fr       */
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

void	print_sorted_env(t_shell *shell, char **env, int n)
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
		printf("declare -x %s=\"%s\"\n", aux, ft_get_env_val(shell, aux));
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

int	modifyenv(t_shell *shell, char **command, int n)
{
	int		i;
	char	**act_env;
	char	*newval;
	int		ret;

	i = 0;
	ret = 0;
	while (command[++i])
	{
		if (command[i][0] == '=' || ft_isdigit(command[i][0]))
		{
			printf("bash: export: %s : not a valid identifier\n", command[i]);
			ret = 1;
			continue ;
		}
		else if (ft_get_env_pos(shell->envp, command[i]) >= 0)
		{
			newval = get_new_val(command[i]);
			ft_set_env_val(shell, command[i], get_new_val(command[i]),
				ft_get_env_pos(shell->envp, command[i]));
			if (newval)
				free(newval);
			continue ;
		}
		act_env = new_env(shell->envp, n++, 1, (command[i]));
		free(shell->envp);
		shell->envp = act_env;
	}
	return (ret);
}


int	ft_export(t_shell *shell, int argnum)
{
	char	**env_cpy;
	int		n;
	
	n = 0;
	if (!shell->envp)
		return (1);
	while (shell->envp[n])
		n++;
	// printf("-----ARGNUM = %i\n", argnum);
	if (shell->cmds[argnum][1] == NULL)
	{
		env_cpy = new_env(shell->envp, n, 0, NULL);
		print_sorted_env(shell, env_cpy, n);
		free_env(env_cpy);
	}
	else
	{
		return (modifyenv(shell, (char **)shell->cmds[argnum], n));
	}
	return (0);
}
