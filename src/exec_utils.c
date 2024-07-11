/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:50 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/11 19:56:19 by kkoval           ###   ########.fr       */
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

int  handle_pipes(t_ms *ms)
{
    int i;

    if (ms->cmnds_num  == 0) // linea vacia? no creo que llege hasta aqui protegemos de momento
    {
        dprintf(2, "linea vacia ha llegado al ejecutor\n");
        return (-1);
    }
    if (ms->cmnds_num  == 1)
    {
        dprintf(2, "Un solo comando no requiere pipes\n");
        return (0);
    }
    ms->pipes = malloc(sizeof(int *) * (ms->cmnds_num));
    if (!ms->pipes)
        return (-1);
    i = 0;
    while (i < ms->cmnds_num -1)
    {
        ms->pipes[i] = malloc(sizeof(int) * 2);
        if (!ms->pipes[i])
        // tambien liberar otros si se han creado ft_close_program (que llamara otros close de cada tipo que los libera)
            return (-1) ; 
        i++;
    }
    ms->pipes[i] = NULL;
    i = 0;
    while (i < ms->cmnds_num  -1)
    {
        if (pipe(ms->pipes[i]) == -1)
        {
            dprintf(2, "ha fallado la pipe\n");
            // cerrar las que se han abierto!!
            return (-1);
        }
        dprintf(2, "pipe %d (%d, %d) \n", i, ms->pipes[i][0], ms->pipes[i][1]);
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