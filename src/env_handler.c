/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/09 18:25:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

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

// converts a list to a char **
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
		aux = ft_strjoin(env->v_name, "="); // needs to be checkes for NULL?
		env_a[i] = ft_strjoin(aux, env->v_cont);
		free (aux);
		i++;
		env = env->next;
	}
	env_a[i] = NULL;
	return (env_a);
}

//it assigns names and values to the nodes
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
	(*current)->v_cont = ft_substr(env_p, equal + 1, env_len - equal + 1);
	if ((*current)->v_name == NULL || (*current)->v_cont == NULL)
		return (-1);
	(*current)->next = NULL;
	return (0);
}

//goes through the char ** and takes each char and creates nodes
// maybe should 
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
