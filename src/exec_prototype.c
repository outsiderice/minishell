/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prototype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/04 15:53:18 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char **ft_get_paths(t_env *env)
{
    char	**paths;
    while(env != NULL && ft_str_compare(env->v_name, "PATH") == 1)
        env = env->next;
    if (env == NULL)
		return (NULL);
	paths = ft_split(env->v_cont, ':');
	if (!paths)
		return (NULL);
    return (paths);
}

int	is_file_in_dir(char *file, char *dir)
{
	DIR 			*dirp;
    struct dirent	*entry;

    // Open the directory stream
    dirp = opendir(dir);
	//printf("%s\n", dir);
    if (dirp == NULL)
    {
        return (1);
    }
    // Read directory entries
	entry = readdir(dirp);
    while (entry != NULL && ft_str_compare(file, entry->d_name) == 1)
	{
		//printf("dentro de entry --------> %s\n", entry->d_name);
		entry = readdir(dirp); // it returns the next file
	}
    // Close the directory stream
    if (closedir(dirp) != 0) // that this fucks up our entry?
	{
        perror("closedir");
        return (1);
    }
	if (entry == NULL )
		return (1);
    return (0);
}

char	*ft_join_path(char *path, char *cmd)
{
	char	*res;
	char	*aux;

	aux = ft_strjoin(path, "/");
	res = ft_strjoin(aux, cmd);
	free(aux); // is it necessary?
	return (res); 
}

int ft_exec_cmd(char **args, t_env *env) 
{
    int i;
    char *cmd;
    char **paths;
    char **envp;
    int exit_status;

    i = 0;
    cmd = args[0];
    exit_status = 0;
    envp = ft_list_to_array(env);
    if (envp == NULL)
        return (-1); // handle this error
    paths = ft_get_paths(env);
    if (paths == NULL)
        return (-1); //handle this error, no path variable in env
    while (paths[i] != NULL && is_file_in_dir(cmd, paths[i]))
        i++;
    if (paths[i] == NULL) 
    {
        exit_status = execve(cmd, args, envp);
        free_arr(envp);
        if (exit_status == -1) 
        {
            printf("command not found\n"); //change exitstatus to 127
            return (127);
        }
    }
    else 
    {
        exit_status = execve(ft_join_path(paths[i], cmd), args, envp);
        free_arr(envp);
        if (exit_status == -1) 
        {
            perror("execve");
            exit(1);
        }
    }
    return (exit_status);
}

int ft_exec(t_ms *ms, t_args *args)
{
    int i;
    t_args  *args_first;
    
    i = 0;
	args_first = args;
    if (handle_pipes(ms) == -1)
    {
        printf("el numero de commandos es %d\n", ms->cmnds_num);
        return (-1);
    }

    if (handle_pids(ms) == -1)
    {
        dprintf(2, "ha fallado algo en handle_pid\n");
        return (-1);
    }
    while (i < ms->cmnds_num)
    {
        if (i != ms->cmnds_num - 1 && pipe(ms->pipes[i]) == -1)
		{
			printf("error in pipe\n");
			return (1);
		}
        if (is_builtin(args->argv[0]) == 1)
        {
			if (args->fd[1] != -2 && args->fd[1] != -1)
				handle_builtins(ms, args, args->fd[1]);
			else if (i != ms->cmnds_num -1)
				handle_builtins(ms, args, ms->pipes[i][1]);
			else
				handle_builtins(ms, args, 1);
            // hace falta gestionar el enganche entre comandos y builtins
        }
        else
        {
             ms->pid[i] = fork();
             if (ms->pid[i] == 0)
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
                //dprintf(2, "------------------  Command Start     ------------------\n");
                ft_exec_cmd(args->argv, ms->env);
                ft_close_fd(args_first);
                //dprintf(2, "------------------  Command Finished  ------------------\n");
             }
        }
        //dprintf(2, "next args\n");    
        args = args->next;
        i++;
    }
    i = 0;
    int stat;
    if(ms->cmnds_num > 1)
    	close_pipes(ms->pipes, 0, ms->cmnds_num, ms->cmnds_num - 1);
    while (i < ms->cmnds_num)
    {
        waitpid(ms->pid[i], &stat, 0);
        i++;
    }
	ft_close_fd(args_first);
    return (0);
}

