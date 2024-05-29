/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/29 18:14:57 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// env shows all of the enviroment variables
// STDOUT_FILENO is equivalent to using the integer 1, is file descriptor for standart output.
// EXIT_SUCCESS); // macro variable that equals 0

/* TO DO
	1. what if env is empty?
	2. what is there is no path in env?
	3. in Bash, an exit status of 126 ----> 
		bash-3.2$ env Music/
		env: Music/: Permission denied
		bash-3.2$ echo $?
		126

*/

int	ft_env(t_env *env_list) //linked structure,
{
	while (env_list != NULL)
	{
		ft_putstr_fd(env_list->v_name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env_list->v_cont, STDOUT_FILENO);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS); // macro variable that equals 0
}

// I was writing this to test my ft_env, but also this function is to copy
// env variables and to create our list of env variables, as dup does not work 
// as I though and we have to do it manually
// this function will be at least 2 or 3 separated functions
t_env	*start_env(char **env)
{
	int				i;
	unsigned int	equal_chr;

	t_env	*new_env;
	t_env	*first;
	t_env	*follow;

	i = 0;
	new_env = NULL;
	if (env[0] == NULL)
		return (new_env);
	new_env = malloc(sizeof(t_env) * 1);
	if (!new_env)
		return (NULL);
	first = new_env;
	while (env[i] != NULL)
	{
		follow = malloc(sizeof(t_env) * 1);
		if (!follow)
			return (NULL);

		equal_chr = ft_strchr(const char env[i])
		aux->v_name = ft_substr(env[i], equal_chr, ft_strlen(env[i]));
		aux->v_cont = ft_substr(env[i], equal_chr + 1, ft_strlen(env[i]));
		new_env->next = aux;

		i++;
	}
	return (new_env);
}
