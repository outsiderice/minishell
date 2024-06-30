/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:18 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/30 13:52:17 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* DESCRIPTION FROM SHELL MANUAL
	Change the current working directory to directory. If directory is not supplied, the value of the HOME shell variable is used. If the shell variable CDPATH exists, 
	it is used as a search path: each directory name in CDPATH is searched for directory, with alternative directory names in CDPATH separated by a colon (‘:’). 
	If directory begins with a slash, CDPATH is not used.
*/

/* How cd should behave:
1. cd with no arguments => NOT ASKED IN EVAL SHEET
	1. should go to HOME path (HOME env variable)
	2. should change it's current PWD (to HOME path) and OLDPWD(will reflect it's previous PWD)
2. cd ..
	1. goes to previous directory
	2. changes PWD and OLDPWD
3. cd relative path should not start with /
4. cd absolut path should start with /
5. cd . => we remain in the same directory, however the OLDPWD is changed to current PWD
5. DOUBTS:
	1. Should we impliment cd with no arguments? Some projects have it, but it is not specified in PDF
	2. Do we have to check permissions to enter specific directories?
	3. How to check if the directory exists? 
	4. How far can we cd back? -- Should not cd more that to \
*/

//To list the directories (or files) 
//in a directory in C, you can use the POSIX opendir, readdir, and closedir functions, which are part of the dirent.h


int	ft_abs_path(char *path)
{
	if (chdir(path) == -1) //chdir sets erno
		return (-1);
	return (0);
}

int	ft_rel_path(char *path)
{
	char	*pwd;
	char	*abs_path;

	pwd = getcwd(NULL, 0);
	abs_path = NULL;
	if (pwd == NULL)
		return (-1);
	if (is_file_in_dir(path, pwd) == 1)
	{
		printf("bash: cd: %s: No such file or directory", path);
		return (-1);
	}
	abs_path = ft_strjoin(pwd, "/");
	abs_path = ft_strjoin(abs_path, path);
	if (chdir(abs_path) == -1)
	{
		ft_putendl_fd("bash: cd: cd did not worked", STDOUT_FILENO); //check for this error message
		return (-1);
	}
	free(abs_path);
	free(pwd);
	return (0);
}

int	ft_cd_var(t_env *env, char *var_name)
{
	char	*path;

	path = get_env_cont(env, var_name);
	if (!path)
	{
		printf("bash: cd: %s NOT SET", var_name);
		return (-1);
	}
	if (chdir(path) == -1)
	{
		ft_putendl_fd("bash: cd: cd did not worked", STDOUT_FILENO); //check for this error message
		return (-1);
	}
	free(path);
	return (0);
}


int	ft_cd(t_env *env, char **args)
{
	char	*path;
	char	*home;
	
	//g_var possible global variable
	path = NULL;
	if(args[1] && args[2]) // necesita una funcion que diga la len de args
	{
		ft_putstr_fd("eggshell: cd: too many arguments\n", 1);
		return (1);
	}
	if (!args[1] || ft_str_compare(args[1], "~") == 0)
	{
		path = ft_cd_var(env, "HOME");
		if (!path)
			return (1);	
		return (0);
	}
	if (ft_str_compare(args[1], "-") == 0)
	{
		path = ft_cd_var(env, "OLDPWD");
		if (!path)
			return (1);	
		return (0);
	}
	if (ft_rel_path(args[1]) == -1 && ft_abs_path(args[1] == -1))
		
		printf("bash: cd: %s: No such file or directory", args[1]);
	free(path);
	add_home_path(args[1]);
	free(path);
	return (0);
}

/*
int	main(int ac, char **av)
{
	char	**args;
	int		i;
	int		x;
	int 	j;
	
	if (ac < 2)
		return (0);
	args = malloc(sizeof(char *) * ac);
	if (!args)
		return (0);
	i = 1;
	x = 0;
	while (i < ac)
	{
		args[x] = strdup(av[i]);
		if (!args[x])
		{
			j = 0;
			while (j < x)
			{
				free(args[j]);
				j++;
			}
			free(args);
			return (0);
		}
		//printf("%s\n", args[x]);
		i++;
		x++;
	}
	args[x] = NULL;
 	ft_exit(args);
	j = 0;
	while (args[j] != NULL)
    {
        free(args[j]);
		j++;
    }
    free(args);
	return (1);
}



/* FUNCTION PROTOTYPES
	1. int chdir(const char *path) is used to change the current working directory of the calling process.
	Parameter:
		 A pointer to a string that specifies the path to the new working directory.
	Return Value:
		On success, chdir returns 0.
		On failure, it returns -1 and sets the errno variable to indicate the error.
	Common Error Codes
		ENOENT: The directory specified by path does not exist.
		EACCES: Permission is denied to change to the specified directory.
		ENOTDIR: A component of the path is not a directory.
*/
