/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:58:27 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/06 19:40:14 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// COMPARES 2 STRINGS AND THEIR LEN, 0 = EQUALS
int	ft_str_compare(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	return (1);
}

//RETURNS THE CONTENT OF A VARIABLE or NULL IF IT DOESNT EXIST
char	*get_env_cont(t_env *env, char *str)
{
	char	*var;

	var = NULL;
	while (env != NULL)
	{
		if (ft_str_compare(env->v_name, str) == 0)
		{
			// var = ft_strdup(env->v_cont);
			// if (!var)
			// 	return (NULL);
			var = env->v_cont;
			return (var);
		}
		env = env->next;
	}
	return (var);
}

int	ft_args_len(char **args)
{
	int	len;

	len = 0;
	while (args[len] != NULL)
		len++;
	return (len);
}

//IT SETS ENV VARIABLE CONTENT
int	ft_set_env_cont(t_env *env, char *name, char *cont)
{
	while (env != NULL)
	{
		if (ft_str_compare(env->v_name, name) == 0)
		{
			free(env->v_cont);
			env->v_cont = ft_strdup(cont);
			if (!env->v_cont)
				return (-1);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

void	ft_free_node(t_env *env)
{
	if (env->v_name != NULL)
		free(env->v_name);
	if (env->v_cont != NULL)
		free(env->v_cont);
	free(env);
}
