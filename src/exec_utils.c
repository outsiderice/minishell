
#include "../inc/minishell.h"

int handle_pipe(t_ms *ms)
{
    int pipes;

    pipes = ft_pipes_len(ms->args);
    if ( pipes == 0)
        ms->pid = malloc(sizeof(int) * ms->args)
}

int ft_pipes_len(t_args *args)
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