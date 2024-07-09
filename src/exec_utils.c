
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
    if (pipes == 0)
        ms->pid = malloc(sizeof(int) * pipes_num);
}