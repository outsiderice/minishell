/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:49:12 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/09 18:30:42 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_print_env(t_env *env_list, int fd)
{
    ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_list->v_name, fd);
	ft_putchar_fd('=', fd);
	ft_putchar_fd('"', fd);
	ft_putstr_fd(env_list->v_cont, fd);
	ft_putendl_fd("\"", fd);
	return;
}

int	is_var_in_list(t_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_str_compare(env_list->v_name, name) == 0)
			return (0);
		env_list = env_list->next;
	}
	return (1);
}