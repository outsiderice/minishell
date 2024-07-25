/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/18 01:37:17 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// env shows all of the enviroment variables
// STDOUT_FILENO is equivalent to using the integer 1, is file descriptor for standart output.
// EXIT_SUCCESS); // macro variable that equals 0

/* TO CONSIDER
	1. what if env is empty?
	2. what is there is no path in env?
	3. in Bash, an exit status of 126 ----> 
		bash-3.2$ env Music/
		env: Music/: Permission denied
		bash-3.2$ echo $?
		126
*/

int	ft_env(t_env *env_list, int fd)
{
	while (env_list != NULL)
	{
		ft_putstr_fd(env_list->v_name, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(env_list->v_cont, fd);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS); // macro variable that equals 0
}
