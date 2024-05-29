/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 16:22:57 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//echo -n "hola" "hola"
//echo with no argument print \n
// echo -n with with no arguments just shows the next line
// how to check for unexpected error for 1

int	ft_echo(t_args *args)
{
	if (args == NULL)
		ft_putchar_fd("\n", STDOUT_FILENO);
	else if (!ft_strncmp(args->arg, "-n", 2) && ft_strlen(args->arg) == 2)
		ft_print_args(args->next);
	else if (args != NULL)
	{	
		ft_print_args(args);
		ft_putchar_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

void	ft_print_args(t_args *args)
{
	while (args != NULL)
	{
		ft_putstr_fd(args->arg, STDOUT_FILENO);
		args = args->next;
		if (args != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

// int	main(int argc, char **argv)
// {
// 	ft_echo(argv);
// }