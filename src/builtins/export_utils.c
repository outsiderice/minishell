/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:49:12 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/05 17:45:06 by kkoval           ###   ########.fr       */
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