/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:24:15 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/02 12:14:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		free(current->v_name);
		free(current->v_cont);
		free(current);
		current = current->next;
	}
}