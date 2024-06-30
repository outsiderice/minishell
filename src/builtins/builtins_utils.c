/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:27:10 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/30 12:56:40 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdio.h>

// this functions compares without a need of strlen
int ft_str_compare(char *str1, char *str2)
{
    int i;
    
	i = 0;
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

//checks if there is a specific variable and returns its content or NULL if it does not exist
char	*get_env_cont(t_env *env, char *str)
{
	char	*var;

	var = NULL;
	while (env != NULL)
	{
		if (ft_str_compare(env->v_name, strn) == 0)
		{
			var = ft_strdup(env->v_cont);
			if (!var)
				return (NULL);
			return (var);
		}
		env = env->next;
	}
	//possible error printing function depending on the int
	return (var);
}
