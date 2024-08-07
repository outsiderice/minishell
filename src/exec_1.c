/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/07 17:15:51 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_exec_cmd(t_ms *ms, char **args, t_env *env) 
{
    char    *cmd;
    char    *path;
	char	**paths;

    cmd = args[0];
	paths = ft_get_paths(env);
    path = ft_find_path(cmd, paths);
    if (path != NULL)
	{
        cmd = ft_join_path(path, cmd);
	}
	ms->envp = ft_list_to_array(env);
    if (execve(cmd, args, ms->envp) == -1) 
    {
        ft_putstr_fd("command not found\n", 2);
        free_arr(ms->envp);
		free_arr(paths);
		free(path);
        exit (127);
    }
    free(path);
	free_arr(paths);
    //free_arr(ms->envp);
    return (0);
}

void ft_exec_child(t_ms *ms, t_args *args, int i)
{   
    if (args->fd[0] != -2 && args->fd[0] != -1)
        dup2(args->fd[0], STDIN_FILENO);
    else if (i != 0)
        dup2(ms->pipes[i-1][0], STDIN_FILENO);
    if (args->fd[1] != -2 && args->fd[1] != -1)
        dup2(args->fd[1], STDOUT_FILENO);
    else if (i !=  ms->cmnds_num - 1)
        dup2(ms->pipes[i][1], STDOUT_FILENO);
    if (ms->cmnds_num > 1)
        close_pipes(ms->pipes, 0, i, ms->cmnds_num - 1);
    ft_close_fd(ms->args);
    ms->exitstatus = ft_exec_cmd(ms, args->argv, ms->env);
	return;
}

void ft_exec_builtin(t_ms *ms, t_args *args, int i)
{
    int out_fd;

    out_fd = 1;
    if (args->fd[1] != -2 && args->fd[1] != -1)
        out_fd = args->fd[1];
    else if (i != ms->cmnds_num -1)
        out_fd = ms->pipes[i][1];
    ms->exitstatus = handle_builtins(ms, args, out_fd);
    //printf("%d\n", ms->exitstatus);
	return;
}

int ft_exec_args(t_ms *ms, t_args *args)
{
    int     i;

    i = 0;
    while (i < ms->cmnds_num)
    {
        if (i != ms->cmnds_num - 1 && pipe(ms->pipes[i]) == -1)
            //lliberar todo y cerrar programa??
			return (1);
        if (ms->cmnds_num == 1 && is_builtin(args->argv[0]) == 1)
            ft_exec_builtin(ms, args, i);
        else
        {
            ms->pid[i] = fork();
            if (ms->pid[i] == 0)
            {
                if (is_builtin(args->argv[0]) == 1)
                {
                    ft_exec_builtin(ms, args, i);
                    exit (ms->exitstatus);
                }
                else
                    ft_exec_child(ms, args, i);
            }                
        }
        args = args->next;
        i++;
    }
    close_pipes(ms->pipes, 0, ms->cmnds_num, ms->cmnds_num - 1);
    //wait_pids(ms);
    return (0);
}

int ft_exec(t_ms *ms, t_args *args)
{	    
	int stat;
    int i;

	i = 0;
    if (handle_pipes(ms) == -1 || handle_pids(ms) == -1)
	{
        //lliberar todo y cerrar programa??
        return (1);
	}
    ft_exec_args(ms, args);
    while (i < ms->cmnds_num)
    {
        waitpid(ms->pid[i], &stat, 0);
        printf("%d\n", stat);
        ms->exitstatus = WEXITSTATUS(stat);
        printf("exit status es %d\n", ms->exitstatus);
        i++;
    }
	ft_close_fd(ms->args);
    return (0);
}
