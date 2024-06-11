#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
//#include <errno.h>
#include "../lib/libft/include/libft.h"
#include "../inc/minishell.h"

// gcc -I../lib/libft/include exec_prototype.c -L../lib/libft -lft -o executable

/*typedef struct s_env
{
	char			*v_name;
	char			*v_cont;
	struct s_env	*next;
}	t_env;

typedef struct s_args
{
	int				fd[2];
	//int				argc;
	char			**argv;
	struct s_args	*next;
}	t_args;

typedef struct s_ms
{
	t_env		*env;
	t_args		*args;
	//char		**env_p;
	//char		**paths;
	int			sh_lvl;
	int			exec_value;
	int			pid;
}	t_ms;

void	ft_init_ms(t_ms *ms)
{
	ms->env = NULL;
	ms->args = NULL;
	ms->exec_value = -1;
	ms->sh_lvl = -1; //HOW?
	ms->pid = getpid();
	}
	*/


// int	ft_lstlen(t_env *env)
// {
// 	int	len;

// 	len = 0;
// 	while (env != NULL)
// 	{
// 		env = env->next;
// 		len++;
// 	}
// 	return (len);
// }

/*
char **ft_list_to_array(t_env *env)
{
	char	**env_a;
	char 	*aux;
	int		i;

	env_a = malloc(sizeof(char *) * ft_lstlen(env) + 1);
	if (!env_a)
		return (NULL);
	i = 0;
	while (env != NULL) 
	{
		aux = ft_strjoin(env->v_name, "="); // needs to be checkes for NULL?
		env_a[i] = ft_strjoin(aux, env->v_cont);
		free (aux);
		i++;
		env = env->next;
	}
	env_a[i] = NULL;
	return (env_a);
}

int ft_str_compare(char *str1, char *str2)
{
    int i;
    
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
        return (0);
	return (1);
}


int		ft_assign(char *env_p, t_env **current)
{
	int		equal;
	char	*equal_ptr;
	int		env_len;

	if (env_p == NULL) //Error, nothing to save
		return (-1);
	equal_ptr = ft_strchr(env_p, '=');
	if (equal_ptr == NULL) //Error
		return (-1);
	env_len = ft_strlen(env_p); 
	equal = equal_ptr - env_p; // maybe wrong
    (*current)->v_name = ft_substr(env_p, 0, equal);
	(*current)->v_cont = ft_substr(env_p, equal + 1, env_len);
	if ((*current)->v_name == NULL || (*current)->v_cont == NULL)
		return (-1); // something went wrong
	(*current)->next = NULL;
	return (0); // everything is ok
}


t_env	*start_env(char **env_p)
{
    int		i;
    t_env	*first;
    t_env	*current;
	t_env	*prev;
    
    i = 0;
	if (env_p == NULL || env_p[0] == NULL)
        return (NULL);
	while (env_p[i] != NULL)
	{
		current = malloc(sizeof(t_env) * 1);
		if (!current)
			return (NULL);
		if (ft_assign(env_p[i], &current) == -1)
			return (NULL);
		if (i == 0)
			first = current;
		else
			prev->next = current;
		prev = current;
		i++;
	}
	return (first);
}
*/

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

	args = ms->args;
	while (args != NULL)
	{
		if (is_builtin(args->argv[0]) == 0)
		{
			if (handle_builtins(ms) == -1) // check for error
				return (-1); //error
		}
		else
		{
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
		args = args->next;
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