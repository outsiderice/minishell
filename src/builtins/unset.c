/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:31 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/11 00:11:48 by kate             ###   ########.fr       */
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

int	ft_unset_args(t_env **env, char *arg)
{
	if (arg != NULL)
		ft_remove_env_var(env, arg);
	return (0);
}

int	ft_unset(t_ms *ms, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		return (0);
	while (args[i] != NULL)
	{
		ft_unset_args(&(ms->env), args[i]);
		if (ft_str_compare(args[i], "OLDPWD") == 0)
		{
			free(ms->old_pwd);
			ms->old_pwd = NULL;
		}
		i++;
	}
	return (0);
}
