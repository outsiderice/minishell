/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:50 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/09 18:27:04 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_t_args_len(t_args *args)
{
    int len;

    len = 0;
    while (args != NULL)
    {
        args = args->next;
        len++;
    }
    return (len);
}

int handle_pipe(t_ms *ms)
{
    int pipes_num;

    pipes_num = ft_t_args_len(ms->args);
    if (pipes_num)
    ms->pid = malloc(sizeof(int) * pipes_num);
    if (!ms->pid)
        return (-1);
    return (0);
}