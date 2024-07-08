/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:18 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/07 23:49:18 by kate             ###   ########.fr       */
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

5. DOUBTS:
	2. Do we have to check permissions to enter specific directories?
*/

int ft_change_pwd(t_ms *ms)
{
	char	*aux;

	aux = ms->pwd;
	ms->pwd = getcwd(NULL, 0);
	if (ms->pwd == NULL)
		return (-1);
	ms->old_pwd = aux;
	printf("oldpwd -- %s, new pwd -- %s",ms->pwd, ms->old_pwd);
	ft_set_env_cont(ms->env, "PWD", ms->pwd);
	ft_set_env_cont(ms->env, "OLDPWD", ms->old_pwd);
	return (0);
}

int	ft_get_old_path(t_ms *ms)
{
	char	*path;
	char	*aux;

	path = get_env_cont(ms->env, "OLDPWD");
	aux = path;
	if (!path)
	{ 
		if (ms->old_pwd == NULL)
		{
			printf("bash: cd: OLDPWD not set");
			return (-1);
		}
		else 
			aux = ms->old_pwd;
	}
	if (chdir(aux) == -1)
	{
		printf("bash: cd: %s No such file or directory\n", aux);
		return (-1);
	}
	printf("%s\n", aux);
	ft_change_pwd(ms);
	return (0);
}

char	*ft_from_abs_path(t_ms *ms, char *arg)
{
	char	*path;

	path = get_env_cont(ms->env, "HOME");
	if (!path)
	{
		printf("bash: cd: HOME NOT SET");
		return (NULL);
	}
	if (arg == NULL || arg[1] == '\0')
		return (path);
	arg++;
	path = ft_strjoin(path, arg);
	return (path);
}

int	ft_cd(t_ms *ms, char **args)
{
	char	*path;
	struct stat	sb;
	
	//g_var possible global variable
	path = NULL;
	if (ft_args_len(args) > 2)
	{
		ft_putstr_fd("eggshell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (ft_str_compare(args[1], "-") == 0)
		return (ft_get_old_path(ms));
	else if (!args[1] || args[1][0] == '~')
		path = ft_from_abs_path(ms, args[1]);
	else
		path = ft_strdup(args[1]);
	
	if (chdir(path) == -1)
	{
		if (stat(path, &sb) == 0)
		{
			printf("bash: cd: %s Not a directory", path);
			free(path);
		}
		else 
			printf("bash: cd: %s No such file or directory\n", path);
		return (-1);
	}
	ft_change_pwd(ms);
	if (path != NULL)
		free(path);
	//printf("old pwd es %s, newpwd es %s\n", ms->old_pwd, ms->pwd);
	return (0);
}
