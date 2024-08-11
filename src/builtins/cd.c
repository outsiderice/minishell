/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:02:52 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/11 12:42:58 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_change_pwd(t_ms *ms)
{
	char	buffer[1024];

	if (ms->old_pwd != NULL)
		free(ms->old_pwd);
	ms->old_pwd = ft_strdup(ms->pwd);
	if (ms->old_pwd == NULL)
		return (-1);
	free(ms->pwd);
	ms->pwd = ft_strdup(getcwd(buffer, 1024));
	if (ms->pwd == NULL)
		return (-1);
	ft_set_env_cont(ms->env, "OLDPWD", ms->old_pwd);
	ft_set_env_cont(ms->env, "PWD", ms->pwd);
	return (0);
}

int	ft_get_old_path(t_ms *ms, int fd)
{
	char	*path;
	char	*aux;

	path = get_env_cont(ms->env, "OLDPWD");
	aux = path;
	if (!path)
	{
		if (ms->old_pwd == NULL)
		{
			error_msg("cd: OLDPWD not set", NULL);
			return (1);
		}
		else
			aux = ms->old_pwd;
	}
	if (chdir(aux) == -1)
	{
		error_msg2("cd: ", aux, " No such file or directory", 1);
		return (1);
	}
	ft_putstr_fd(aux, fd);
	ft_putstr_fd("\n", fd);
	free(path);
	ft_change_pwd(ms);
	return (0);
}

char	*ft_from_abs_path(t_ms *ms, char *arg)
{
	char	*path;
	char	*aux;

	path = get_env_cont(ms->env, "HOME");
	if (!path)
	{
		error_msg("cd: HOME NOT SET", NULL);
		return (NULL);
	}
	if (arg == NULL || arg[1] == '\0')
		return (path);
	arg++;
	aux = ft_strjoin(path, arg);
	free(path);
	return (aux);
}

int	ft_exec_path(char *path)
{
	struct stat	sb;

	if (chdir(path) == -1)
	{
		if (stat(path, &sb) == 0)
		{
			ft_putstr_fd("eggshell: ", 2);
			error_msg2("cd: ", path, ": Not a directory", 1);
			free(path);
		}
		else
		{
			ft_putstr_fd("eggshell: ", 2);
			error_msg2("cd: ", path, ": No such file or directory", 1);
			free(path);
		}
		return (1);
	}
	return (0);
}

int	ft_cd(t_ms *ms, char **args, int fd)
{
	char		*path;

	path = NULL;
	if (ft_str_compare(args[1], "-") == 0)
		return (ft_get_old_path(ms, fd));
	else if (!args[1] || args[1][0] == '~')
	{
		path = ft_from_abs_path(ms, args[1]);
		if (path == NULL)
			return (1);
	}
	else
		path = ft_strdup(args[1]);
	if (ft_exec_path(path) != 0)
		return (1);
	ft_change_pwd(ms);
	free(path);
	return (0);
}
