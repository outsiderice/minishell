/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:52 by kate              #+#    #+#             */
/*   Updated: 2024/08/11 00:26:52 by kate             ###   ########.fr       */
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

    dirp = opendir(dir);
    if (dirp == NULL)
		return (1);
	entry = readdir(dirp);
    while (entry != NULL && ft_str_compare(file, entry->d_name) == 1)
		entry = readdir(dirp);
    if (closedir(dirp) != 0)
		return (1);
	if (entry == NULL)
	    return (1);
    return (0);
}

char	*ft_join_path(char *path, char *cmd)
{
	char	*res;
	char	*aux;

	aux = ft_strjoin(path, "/");
	res = ft_strjoin(aux, cmd);
	free(aux);
	return (res); 
}

char *ft_find_path(char *file, char **paths)
{
    int i;

    i = 0;
    if (paths == NULL)
        return (NULL); 
    while (paths[i] != NULL && is_file_in_dir(file, paths[i]))
        i++;
    return (paths[i]);
}

int check_access(t_ms *ms, char *file)
{
    if (access(file, F_OK) == -1)
    {
        error_msg(file, " No such file or directory");
        ms->exitstatus = 1;
        return (1);
    }
    else if (access(file, W_OK) == -1)
    {
        error_msg(file, " Permisson denied");
        ms->exitstatus = 1;
        return (1);
    }
    return (0);
}
