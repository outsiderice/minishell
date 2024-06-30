/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prototype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/30 17:57:35 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
//#include <errno.h>
#include "../lib/libft/libft.h"
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
    if (dirp == NULL) {
        perror("opendir");
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


int	ft_exec_cmd(char **args, t_env *env)
{
	int		i;
	char	*cmd;
	char	**paths;
	char	**envp;

	i = 0;
	cmd = args[0];

	envp = ft_list_to_array(env);
	if (envp == NULL)
		return (-1); // handle this error
	paths = ft_get_paths(env);
	if (paths == NULL)
		return (-1); //handle this error, no path variable in env
	while (paths[i] != NULL && is_file_in_dir(cmd, paths[i]))
		i++;
	if (paths[i] == NULL)
		printf("command not found\n");
	else
	{
		execve(ft_join_path(paths[i], cmd), args, envp);
		printf("%s\n", paths[i]);
	}
	// free envp;
	return (0);
}

int	ft_exec(t_ms *ms)
{
	t_args	*args;
	int	pid;

	printf("HOLA DESDE EXEC\n");
	args = ms->args;
	while (args != NULL)
	{
		printf("args is not null\n");
		if (is_builtin(args->argv[0]) == 1)
		{
			printf("is a builtin\n");
			if (handle_builtins(ms, args) == -1) // check for error
				return (-1); //error
		}
		else
		{
			printf("not a builtin\n");
			if (pipe(args->fd) == -1)
				return (-1); // pipe error
			pid = fork();
			if (pid == 0)
			{
				close(args->fd[0]);
				ft_exec_cmd(args->argv, ms->env); // donde se gestiona exitstatus? aqui ya habra fd
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
		printf("next args\n");
		args = args->next;
		// printf("args->argv[0] = %s\n", args->argv[1]);
	}
	//free(ms->args); // hemos acabado los argumentos
	//ms->args = NULL; // reseteamos la variable
	return (0);
}


/*

int main(int ac, char **av, char **env_p) 
{
	char 	*args[3];
	args[0] = "ls";
	args[1] = "-la";
	args[2] = NULL;
    (void) ac;
    (void) av;
	int		i;
    t_env   *env;
	char	**paths;
	char	*cmd = "ls";
	
	(void) ac;
    (void) av;
	int		i;
	t_ms 	ms;
	t_args	*first;
	t_args	*aux;
	t_args  *args;
	char 	*tmp[3];

	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (1);
	first = args;
	tmp[0] = "ls";
	tmp[1] = "-la";
	tmp[2] = NULL;
	args->argv = tmp;

	aux = malloc(sizeof(t_args) * 1);
	aux->argv = tmp;
	args->next = aux;
	args = args->next;

	aux = malloc(sizeof(t_args) * 1);
	aux->argv = tmp;
	args->next = aux;

	i = 0;
	ft_init_ms(&ms);
	ms.args = first;

    ms.env = start_env(env_p);
	ft_exec(&ms);
	
   return (0);
}*/
