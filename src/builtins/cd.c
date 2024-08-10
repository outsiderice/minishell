/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:02:52 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/10 17:14:58 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_change_pwd(t_ms *ms)
{
	char	*aux;
	char	buffer[1024];

	aux = ms->pwd;
	printf("oldpwd -- %s\n",ms->pwd);
	free(ms->old_pwd);
	ms->old_pwd = ft_strdup(ms->pwd);//cuidado limpiar memoria
	free(ms->pwd);
	ms->pwd = ft_strdup(getcwd(buffer, 1024));
	if (ms->pwd == NULL)
		return (-1);
	
	printf("oldpwd -- %s, new pwd -- %s\n",ms->pwd, ms->old_pwd);
	ft_set_env_cont(ms->env, "PWD", ms->pwd);
	ft_set_env_cont(ms->env, "OLDPWD", ms->old_pwd);
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
	ft_putstr_fd(aux, fd);
	ft_putstr_fd("\n", fd);
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



int	ft_cd(t_ms *ms, char **args, int fd)
{
	char		*path;
	struct stat	sb;

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
	if (chdir(path) == -1)
	{
		if (stat(path, &sb) == 0)
		{
			printf("bash: cd: %s Not a directory", path);
			free(path);
		}
		else
			printf("bash: cd: %s No such file or directory\n", path);
		return (1);
	}
	ft_change_pwd(ms);
	printf("ha llegado aqui y no deberia\n");
	//free_char_ptr(path);
	return (0);
}
