/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:57:40 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/11 17:46:07 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_numeric(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

// counts the nodes to make future malloc to create an char **
int	ft_lstlen(t_env *env)
{
	int	len;

	len = 0;
	while (env != NULL)
	{
		env = env->next;
		len++;
	}
	return (len);
}

char	**ft_list_to_array(t_env *env)
{
	char	**env_a;
	char	*aux;
	int		i;

	env_a = malloc(sizeof(char *) * (ft_lstlen(env) + 1));
	if (!env_a)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		aux = ft_strjoin(env->v_name, "=");
		if (!aux)
		{
			while (i > 0)
			{
				free(env_a[--i]);
			}
			free(env_a);
			return (NULL);
		}
		env_a[i] = ft_strjoin(aux, env->v_cont);
		free(aux);
		if (!env_a[i])
		{
			while (i > 0)
			{
				free(env_a[--i]);
			}
			free(env_a);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	env_a[i] = NULL;
	return (env_a);
}
