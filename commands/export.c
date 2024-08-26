/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:26:29 by sblanco-          #+#    #+#             */
/*   Updated: 2024/08/26 17:53:02 by mmartine         ###   ########.fr       */
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


void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free (env);	
}

void	print_sorted_env(char **env, int n)
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
		printf("%s\n", env[i]);
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

t_shell	modifyenv(t_shell shell, char **command, int n)
{
	int		i;
	char	**act_env;
	int		act;

	i = 0;
	act = 0;
	while (command[++i])
	{
		printf("comando del export actual: %s\n", command[i]);
		if (command[i][0] == '=')
		{
			printf("bash: export: %s : not a valid identifier\n", command[i]);
			continue ;
		}
		act_env = new_env(shell.envp, n, 1, command[i]);
		if (act)
			free(shell.envp);
		shell.envp = act_env;
		act = 1;
		n++;
	}
	return (shell);
}


void	ft_export(t_shell shell)
{
	char	**env_cpy;
	int		n;

	n = 0;
	while (shell.envp[n])
		n++;
	if (shell.cmds[0][1] == NULL)
	{
		env_cpy = new_env(shell.envp, n, 0, NULL);
		print_sorted_env(env_cpy, n);
		free_env(env_cpy);
	}
	else
	{
		shell = modifyenv(shell, (char **)shell.cmds[0], n);
		print_sorted_env(shell.envp, n);
	}
	// printf("Implement export command\n");
}
