/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:31 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/07 15:37:06 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_unset(t_env **env, char **args)
{
    t_env *first;
    t_env *current;
    t_env *prev;
    int i;

    first = *env;
    if (*args == NULL)
        return (0);
    i = 1;
    while (args[i] != NULL)
    {
        current = *env;
        prev = NULL;
        while (current != NULL && ft_str_compare(current->v_name, args[i]) != 0)
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
            // free(current); // Free the structure if needed
        }
        *env = first;
        i++;
    }
    return (0);
}
