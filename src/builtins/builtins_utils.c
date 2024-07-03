/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:00 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/03 15:58:03 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

// this functions compares without a need of strlen
int ft_str_compare(char *str1, char *str2)
{
    int i;
    
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

//checks if there is a specific variable and returns its content or NULL if it does not exist
char	*get_env_cont(t_env *env, char *str)
{
	char	*var;

	var = NULL;
	while (env != NULL)
	{
		if (ft_str_compare(env->v_name, str) == 0)
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

int	ft_args_len(char **args)
{
	int	len;

	len = 0;
	while (args[len] != NULL)
		len++;
	return (len);
}
