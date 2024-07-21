/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:10:49 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/21 18:34:12 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*CHECKS THE VALIDITY OF ARGUMENT TO BE ADDED:
	1. Invalid first character, wrong + position returns error and $? = 1 
	2. In other invalid cases just returns a new line and $? = 0
*/
int		ft_check_export_arg(char *arg)
{
	int	i;
	int	i_plus;

	i = 0;
	i_plus = 0;
	if (ft_isalpha(arg[0]) != 1 && arg[0] != '_')
	{
		printf("eggshell: export: `%s' not a valid identifier\n", arg);
		return (-1);
	}
	while(arg[i] != '\0' && arg[i] != '=')
		i++;
	while(arg[i_plus] != '\0' && arg[i_plus] != '+')
		i_plus++;	
	if (arg[i] == '=' && (i_plus + 1 >= i))
		return (0);
	else
		printf("eggshell: export: `%s' not a valid identifier\n", arg);
	return (-1);
}
//ADD ARGUMENT TO ENV
int	ft_add_to_env(t_env *env_list, char *arg)
{
	t_env 	*aux;
	t_env	*node;

	aux = NULL;
	//if (env_list == NULL) se tiene que gestionar fuera
		//return (-1);
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

// CONTROL FUNCTION, CHOOSES THE RIGHT CASE FOR EXPORT
int	ft_export(t_ms *ms, char **args)
{
	int res;

	res = 0;
	args++;
	if (*args == NULL)
		ft_export_no_args(ms->env);
	else
	{
		while (*args != NULL)
		{
			if (ft_check_export_arg(*args) == 0)
			{
				ft_add_to_env(ms->env, *args);
			}
			else 
				res = 1;
			args++;
		}
	}
	return (res);
}
