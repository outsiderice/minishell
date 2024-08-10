/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:31 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/10 20:27:14 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_remove_env_var(t_env **env, char *arg)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current != NULL && ft_str_compare(current->v_name, arg) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (prev != NULL)
			prev->next = current->next;
		else
			*env = current->next;
		free_node(current);
	}
}

int	ft_unset_args(t_env **env, char **args, int i)
{
	t_env	*first;

	first = *env;
	while (args[i] != NULL)
	{
		ft_remove_env_var(env, args[i]);
		*env = first;
		i++;
	}
	return (0);
}

int	ft_unset(t_ms *ms, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		return (0);
	ft_unset_args(&ms->env, args, i);
	while (args[i] != NULL)
	{
		if (ft_str_compare(args[i], "OLDPWD") == 0)
		{
			free(ms->old_pwd);
			ms->old_pwd = NULL;
		}
		i++;
	}
	return (0);
}
