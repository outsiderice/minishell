/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/05 18:29:00 by kkoval           ###   ########.fr       */
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

int	ft_env(t_env *env_list, t_args *args)
{
	while (env_list != NULL)
	{
		ft_putstr_fd(env_list->v_name, args->fd[1]);
		ft_putchar_fd('=', args->fd[1]);
		ft_putendl_fd(env_list->v_cont, args->fd[1]);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS); // macro variable that equals 0
}
