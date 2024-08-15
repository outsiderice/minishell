/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:07:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/06 14:24:18 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, int start)
{
	char	*var_name;

	if (ft_strncmp(&str[start], "$?", 2) == 0)
		var_name = ft_strdup("?");
	else
		var_name = rm_delimiters(str, start);
	if (!var_name)
		return (NULL);
	return (var_name);
}

// Iterates env to find a node
// Returns a pointer to that node or NULL if it's not found
t_env	*find_env_var(t_env *env, char *var_name)
{
	while (env != NULL && ft_str_compare(env->v_name, var_name) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	return (env);
}
