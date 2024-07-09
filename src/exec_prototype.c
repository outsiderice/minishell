/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prototype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/09 18:13:09 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
//#include <errno.h>
#include "../lib/libft/libft.h"
#include "../inc/minishell.h"


#include <fcntl.h>
#include <unistd.h>

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
        return (1);
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

void handle_redirections(t_args *args) {


    // Input redirection: '<'
    if (args->fd[0] != -1 && args->fd[0] != STDIN_FILENO)
    {
        if (dup2(args->fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(args->fd[0]);
    }

    // Output redirection: '>' and '>>'
    if (args->fd[1] != -1 && args->fd[1] != STDOUT_FILENO) {
        if (dup2(args->fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(args->fd[1]);
    }

    // Here-doc redirection: '<<' (Implement if necessary)
    // You will need to handle here-doc separately, as it involves reading input until a delimiter.
}

int ft_exec_cmd(char **args, t_env *env) {
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
    if (paths[i] == NULL) {
        printf("command not found\n"); //change exitstatus to 127
        return (127);
    } else {
        exit_status = execve(ft_join_path(paths[i], cmd), args, envp);
        if (exit_status == -1) {
            perror("execve");
            exit(1);
        }
    }
    free_arr(envp);
    return (exit_status);
}

/* -------- una puta mierda que no funciona
void handle_pipe(t_args *args)
{
    int auxfd[2];
    while (args != NULL && args->next != NULL)
	{
        if (args->fd[1] == -2 && args->next->fd[0] == -2)
        {
			pipe(auxfd);
			if (pipe(auxfd) == -1) 
			{
                perror("pipe");
                exit(EXIT_FAILURE);
            }
			dup2(args->fd[1], auxfd[1]);
			dup2(args->next->fd[0], auxfd[0]);
            close(auxfd[0]);
            close(auxfd[1]);        
		}
	}
} */

/* 
    1. saber cuantas pipes vamos a necesitar
    2. hacer una matriz de pipes necesarias (estaran todas abiertas)
    3. guardar los pids de los hijos en una int *, asi el padre espera
     que todos sus hijos acaben (a veces da fallos)
    3. se llama al exec como ft_exec que recorre t_args
    4. se forkea y se cierren todos los fds menos los que vamos a necesitar
    5. se hace la execusion
    5. se cierren los fds utilizados y se pasa al siguiente args
    7. se cierran los fds en el papi
    8. waitpid
    9. lliberar pids y pipes de la estructura

*/

int ft_exec(t_ms *ms, t_args *args) 
{
    pid_t pid;

    //if handle_pipe(args);


    while (args != NULL)
    {
        dprintf(2, "------------------  Command Start     ------------------\n");
        if (is_builtin(args->argv[0]) == 1 ) {

            if (handle_builtins(ms, args) == -1) // check for error
                return (-1); //error
        } else {
            dprintf(2, "not a builtin\n");
            pid = fork();
            if (pid == 0) // Child process
            { 
                handle_redirections(args);
                ms->exitstatus = ft_exec_cmd(args->argv, ms->env);
                exit(ms->exitstatus);
            } else if (pid > 0) // Parent process
            { 
                waitpid(pid, &ms->exitstatus, 0);
                ms->exitstatus = WEXITSTATUS(ms->exitstatus);
            } else {
                perror("fork");
                return (-1);
            }
        }
        dprintf(2, "------------------  Command Finished  ------------------\n");
        dprintf(2, "next args\n");
        // if there is next it should read from the previous file
        // so pipe[i][0] has to read from pipe[i - 1][1]
        // if there is an error should we close all the fds?
        
                args = args->next;
    }
    return (0);
}


/*char **ft_get_paths(t_env *env)
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
        return (1);
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


int	ft_exec_cmd(char **args, t_env *env)
{
	int		i;
	char	*cmd;
	char	**paths;
	char	**envp;
	int		exit_status;

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
		printf("command not found\n"); //change exitstatus to 127
		return (127);
	}
	else
	{
		exit_status = execve(ft_join_path(paths[i], cmd), args, envp);
		printf("%s\n", paths[i]);
	}
	free_arr(envp);
	return (exit_status);
}

int	ft_exec(t_ms *ms)
{
	t_args	*args;
	int	pid;

	printf("HOLA DESDE EXEC\n");
	args = ms->args;
	while (args != NULL) //while there're command lines
	{
		if (is_builtin(args->argv[0]) == 1)
		{
			dprintf(2, "is a builtin\n");
			if (handle_builtins(ms, args) == -1) // check for error
				return (-1); //error
		}
		else
		{
			dprintf(2, "not a builtin\n");
			if (pipe(args->fd) == -1)
				return (-1); // pipe error
			pid = fork();
			if (pid == 0)
			{
				close(args->fd[0]);
				ms->exitstatus = ft_exec_cmd(args->argv, ms->env); // donde se gestiona exitstatus? aqui ya habra fd
				close(args->fd[1]);
			}
			else
			{
				close(args->fd[1]);
				//read(fd[0], buffer, algun valor);
				// aqui se hace el dup??
				// aqui se gestionan las señales??
				close(args->fd[0]);
				wait(NULL);
			}
		}
		dprintf(2, "next args\n");
		args = args->next;
	}
	return (0);
}*/
