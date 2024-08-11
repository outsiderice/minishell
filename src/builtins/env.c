/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:57 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/09 20:43:50 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_args *args, t_env *env_list, int fd)
{
	if (args->argv[1] != NULL)
	{
		error_msg("env: too many arguments", NULL);
		return (2);
	}
	while (env_list != NULL)
	{
		ft_putstr_fd(env_list->v_name, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(env_list->v_cont, fd);
		env_list = env_list->next;
	}
	return (0);
}
