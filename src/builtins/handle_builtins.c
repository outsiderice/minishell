/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/10 15:11:13 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *cmd)
{
	if ((ft_str_compare(cmd, "echo") == 0) || (ft_str_compare(cmd, "pwd") == 0) \
	|| (ft_str_compare(cmd, "cd") == 0) || (ft_str_compare(cmd, "env") == 0) || \
	(ft_str_compare(cmd, "export") == 0) || (ft_str_compare(cmd, "unset") == 0) \
	|| (ft_str_compare(cmd, "exit") == 0))
		return (1);
	return (0);
}

int	handle_builtins(t_ms *ms, t_args *args, int fd)
{
	if (ft_str_compare(args->argv[0], "echo") == 0)
		return (ft_echo(args, fd));
	else if (ft_str_compare(args->argv[0], "pwd") == 0)
		return (ft_pwd(fd));
	else if (ft_str_compare(ms->args->argv[0], "cd") == 0)
		return (ft_cd(ms, args->argv, fd));
	else if (ft_str_compare(args->argv[0], "env") == 0)
		return (ft_env(args, ms->env, fd));
	else if (ft_str_compare(args->argv[0], "export") == 0)
		return (ft_export(ms, args->argv, fd));
	else if (ft_str_compare(args->argv[0], "unset") == 0)
		return (ft_unset(ms, args->argv));
	else if (ft_str_compare(args->argv[0], "exit") == 0)
		return (ft_exit(ms, args->argv));
	return (-1);
}
