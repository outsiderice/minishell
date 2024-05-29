/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:45:00 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/29 15:42:55 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// unset deletes the variable from env
// it can have numerous arguments, if some of them don't exist it will 
// skip it and keep on deleting

int ft_unset(t_env **env, t_args *args)
{
    t_env   *first;
	t_env 	*current;
	t_env	*prev;

    first =  env;
    if (args == NULL)
        return (0);
    while (args != NULL)
    {
		current = *env;
		prev = NULL;
		while (current != NULL && ft_str_compare(current->v_name, args->arg) != 0) //until they are same
		{
			prev = current;
			current = current->next;
		}
		if (current != NULL) 
		{
			if (prev != NULL)
				prev->next = current->next;
			else // looks if it is a the env variable that should be deleted
				*env = (*env)->next;
			//free(current) free for this structure is needed
		}
		env = first;
		args = args->next;
    }
}

