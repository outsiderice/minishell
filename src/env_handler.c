/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:08:33 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/21 19:56:57 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// #include "../../lib/libft/include/libft.h"

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

	env_a = malloc(sizeof(char *) * ft_lstlen(env) + 1);
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
	(*current)->v_cont = ft_substr(env_p, equal + 1, env_len);
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

// int	main(int ac, char **av, char **envp)
// {
//     (void) ac;
//     (void) av;
//     t_env	*env;

//     env = start_env(envp);
// 	while (env != NULL)
// 	{
// 		printf("%s", env->v_name);
// 		printf("=");
// 		printf("%s\n", env->v_cont);
// 		env = env->next;
// 	}
//     return (0);
// }