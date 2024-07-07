/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prototype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/07 17:16:46 by kkoval           ###   ########.fr       */
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
    int fd;

    // Input redirection: '<'
    if (args->redir_type == 1) {
        fd = open(args->filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    }

    // Output redirection: '>'
    if (args->redir_type == 3) {
        fd = open(args->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    }

    // Append redirection: '>>'
    if (args->redir_type == 4) {
        fd = open(args->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
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

int ft_exec(t_ms *ms) {
    t_args *args;
    pid_t pid;

    printf("HOLA DESDE EXEC\n");
    args = ms->args;
    // function abrir les pipes de les pipes = int     *arr_pipes = cantidad de nodos en t_args.
    while (args != NULL)
    {
        dprintf(2, "args is not null\n");
        printf("Handling redirections\n");
        //if (args->redir_type != -1) {
        //    handle_redirections(args);
        //}
        if (is_builtin(args->argv[0]) == 1) {
            dprintf(2, "is a builtin\n");
            if (handle_builtins(ms, args) == -1) // check for error
                return (-1); //error
        } else {
            dprintf(2, "not a builtin\n");
            pid = fork();
            if (pid == 0) // Child process
            { 
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
        dprintf(2, "next args\n");
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
