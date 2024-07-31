/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:52 by kate              #+#    #+#             */
/*   Updated: 2024/07/31 13:31:01 by kkoval           ###   ########.fr       */
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
/*
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
}*/

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
