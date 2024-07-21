/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/21 18:33:20 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

//IN CASE THE SHELL LEVEL IS NOT VALID OR NOT PROVIDED IT IS SET TO 1
int ft_create_sh_lvl(t_env *env)
{
	t_env *new;
	
	new = NULL;
	while (env != NULL && env->next != NULL)
		env = env->next;
	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (-1);
	new->v_name = ft_strdup("SHLVL");
	new->v_cont = ft_strdup("1");
	new->next = NULL;

	env->next = new; 
	return (0);
}

int	ft_set_shll_lvl(t_env *env)
{
	t_env *first;

	first = env;
	while (env != NULL)
	{
		if	(ft_str_compare(env->v_name, "SHLVL") == 0)
		{
			if (is_numeric(env->v_cont) == 1) //if case it is numeric
				env->v_cont = ft_itoa(ft_atoi(env->v_cont) + 1);
			else 
				env->v_cont = "1";
			return (1);
		}
		env = env->next;
	}
	printf("no he encontrado SHLS\n");
	if (ft_create_sh_lvl(first) == -1)
		return (-1);
	return (1);
}

int	ft_get_shll_lvl(t_env *env)
{
	while (env != NULL)
	{
		if	(ft_str_compare(env->v_name, "SHLVL") == 0)
		{
			if (is_numeric(env->v_cont) == 1) //if case it is numeric
				return (ft_atoi(env->v_cont));
			return (0);
		}
		env = env->next;
	}
	return (0);
}

//IT ASSIGNS NAMES AND VALUES TO T_ENV NODES
int	ft_assign(char *env_p, t_env **current)
{
	int		equal;
	char	*equal_ptr;
	int		env_len;

	if (env_p == NULL)
		return (-1);
	equal_ptr = ft_strchr(env_p, '=');
	if (equal_ptr == NULL)
		return (-1);
	env_len = ft_strlen(env_p);
	equal = equal_ptr - env_p;
	(*current)->v_name = ft_substr(env_p, 0, equal);
	(*current)->v_cont = ft_substr(env_p, equal + 1, env_len - equal - 1);
	if ((*current)->v_name == NULL || (*current)->v_cont == NULL)
		return (-1);
	(*current)->next = NULL;
	return (0);
}

//GOES THROUGH ENV VARIABLES AND CREATES LINKED T_ENV LIST 
t_env	*start_env(char **env_p)
{
	int		i;
	t_env	*first;
	t_env	*current;
	t_env	*prev;

	i = 0;
	if (env_p == NULL || env_p[0] == NULL)
		return (NULL);
	while (env_p[i] != NULL)
	{
		current = malloc(sizeof(t_env) * 1);
		if (!current)
			return (NULL);
		if (ft_assign(env_p[i], &current) == -1)
			return (NULL);
		if (i == 0)
			first = current;
		else
			prev->next = current;
		prev = current;
		i++;
	}
	return (first);
}
