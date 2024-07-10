/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:05:17 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/07 23:43:58 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* EXPORT
	1. This built-in saves variables passed as enviroment variables if has specific arfument
		NAME=VALUE -> no space between name and value 
	2. export with no arguments
		bash-3.2$ export
		declare -x HOME="/Users/kate"
		declare -x HOMEBREW_CELLAR="/opt/homebrew/Cellar"
		declare -x HOMEBREW_PREFIX="/opt/homebrew"
		declare -x HOMEBREW_REPOSITORY="/opt/homebrew"
		declare -x INFOPATH="/opt/homebrew/share/info:"
		etc... until the end of env list.
*/

/* TO DO: 
	1. Function: Parsing to see if it fits the standart to add it to the list on env variables.
	2. Function: if it does fit add it to env list.
	3. Function: if export has no arguments to go through env list and print it in this structure:
		declare -x HOME="/Users/kate"
		declare -x HOMEBREW_CELLAR="/opt/homebrew/Cellar"
		etc...
	4. How to handle single quotation - A LOT OF FUN TO HANDLE
*/

/*A parameter is an entity that stores values. It can be a name, a number, or one of the special characters listed below. A variable is a parameter denoted by a name. 
A variable has a value and zero or more attributes. Attributes are assigned using the declare builtin command (see the description of the declare builtin in Bash Builtin Commands).
A parameter is set if it has been assigned a value. The null string is a valid value. Once a variable is set, it may be unset only by using the unset builtin command.

A variable may be assigned to by a statement of the form

name=[value]
If value is not given, the variable is assigned the null string. All values undergo tilde expansion, parameter and variable expansion, command substitution, 
arithmetic expansion, and quote removal (see Shell Parameter Expansion). If the variable has its integer attribute set, then value is evaluated as an 
arithmetic expression even if the $((…)) expansion is not used (see Arithmetic Expansion). Word splitting and filename expansion are not performed. 
Assignment statements may also appear as arguments to the alias, declare, typeset, export, readonly, and local builtin commands (declaration commands). 
When in POSIX mode (see 
Bash POSIX Mode), these builtins may appear in a command after one or more instances of the command builtin and retain these assignment statement properties.*/

//FUNCTION TO CHECK IF IT SHOULD BE STORRED

//EXPORT WITH NO ARGUMENTS -> declare -x VARIABLE_NAME="value"\n in alphabetical order si quieres

//CHECKS THE VALIDITY OF ARGUMENT TO BE ADDED 
int		ft_check_export_arg(char *arg)
{
	int	i;
	int	i_plus;

	i = 0;
	i_plus = 0;
	if (ft_isalpha(arg[0]) != 1 && arg[0] != '_') // no es ni letra ni _
		return (0);
	while(arg[i] != '\0' && arg[i] != '=')
		i++;
	while(arg[i_plus] != '\0' && arg[i_plus] != '+')
		i_plus++;
	if (arg[i] == '=' && (i_plus + 1 >= i))
		return (1);
	return (0);
}

//ADD ARGUMENT TO ENV

int	ft_add_to_env(t_env *env_list, char *arg)
{
	t_env 	*aux;
	t_env	*node;

	aux = NULL;
	if (env_list == NULL)
		return (-1);
	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return(-1);
	if (ft_assign(arg, &node) == -1)
		return (-1);
	while (env_list->next != NULL)
	{
		if (ft_str_compare(env_list->v_name, node->v_name) == 0)
			aux = env_list;
		env_list = env_list->next;
	}
	if (ft_str_compare(env_list->v_name, node->v_name) == 0)
		aux = env_list;
	if (aux == NULL)
	{
		aux = malloc(sizeof(t_env) * 1);
		if (!aux)
			return (-1);
		aux->v_name = ft_strdup(node->v_name);
		aux->next = NULL;
		env_list->next = aux;	
	}	
	aux->v_cont = ft_strdup(node->v_cont);
	//printf("New env var added: %s = %s\n", aux->v_name, aux->v_cont );
	free(node);
	return(1);
}

// NO ARGUMENTS, ONLY PRINT ENV_LIST
void	ft_export_no_args(t_env *env_list)
{
	while (env_list != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_list->v_name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(env_list->v_cont, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		env_list = env_list->next;
	}
	return;
}

// CONTROL FUNCTION HAS TO RETURN 0 or 1
int	ft_export(t_ms *ms, char **args) //chekea las opciones no argummentos
{
	args++;
	if (*args == NULL)
		ft_export_no_args(ms->env);
	else
	{
		while (*args != NULL)
		{
			if (ft_check_export_arg(*args) == 1)
				ft_add_to_env(ms->env, *args);
			else
				printf("error\n");
			args++;
		}
	}
	return (0);
}
