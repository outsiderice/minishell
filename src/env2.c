/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:57:40 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/18 18:19:05 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "../inc/minishell.h"
//#include "../../lib/libft/include/libft.h"
#include <stdio.h>

int is_numeric(char *str) 
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
