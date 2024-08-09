/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/09 19:05:37 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//IT CHECKS FOR THE-n OPTION
int	ft_n_check(char *str)
{
	if (str == NULL || *str != '-')
		return (0);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

void	ft_print_args(char **argv, int fd)
{
	while (*argv != NULL)
	{
		ft_putstr_fd(*argv, fd);
		argv++;
		if (*argv != NULL)
			ft_putchar_fd(' ', fd);
	}
}

int	ft_echo(t_args *args, int fd)
{
	int		do_jump;
	char	**argv;

	argv = args->argv;
	argv++;
	do_jump = ft_n_check(*argv);
	while (ft_n_check(*argv) == 1)
		argv++;
	ft_print_args(argv, fd);
	if (do_jump == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}
