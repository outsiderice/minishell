/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:28 by amagnell         ###   ########.fr       */
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

int	ft_env(t_env *env_list)
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
