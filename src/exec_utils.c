/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:50 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/04 15:51:27 by amagnell         ###   ########.fr       */
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

int handle_pipes(t_ms *ms)
{
    int i;

    if (ms->cmnds_num  == 1)
        return (0);
    ms->pipes = malloc(sizeof(int *) * (ms->cmnds_num - 1));
    if (!ms->pipes)
        return (-1);
    i = 0;
    while (i < ms->cmnds_num - 1)
    {
        ms->pipes[i] = malloc(sizeof(int) * 2);
        if (!ms->pipes[i])
            return (-1); 
        i++;
    }
    return (0);
}

int handle_pids(t_ms *ms)
{
    if (ms->cmnds_num == 0)
    {
        dprintf(2, "algo ha ido mal y hay 0 comandos\n");
        return (-1);
    }
    ms->pid = malloc(sizeof(int) * ms->cmnds_num);
    if (!ms->pid)
        return (-1);
    return (0);
}

void    ft_close_fd(t_args *args)
{
    while (args != NULL)
    {
        if (args->fd[0] != -2 && args->fd[0] != -1) // AVOID CLOSING FILENO?
            close(args->fd[0]);
        if (args->fd[1] != -2 && args->fd[1] != -1)
            close(args->fd[1]);
        args = args->next;
    }
}

void close_pipes(int **pipes, int first, int last, int len)
{
    if (len == 0)
        return;
    else
    {
        while (first <= last && first < len)
	    {
		    close(pipes[first][0]);
		    close(pipes[first][1]);
		    free(pipes[first]);
		    ++first;
	    }
	    free(pipes);
        pipes = NULL;
    }
	return;
}
