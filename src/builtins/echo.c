/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/02 18:11:53 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//echo -n "hola" "hola"
//echo with no argument print \n
// echo -n with with no arguments just shows the next line
// how to check for unexpected error for 1

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (*args == NULL)
		ft_putchar_fd("\n", STDOUT_FILENO);
	else if (ft_str_compare(*args, "-n") == 0)
		ft_print_args(args[i++]);
	else if (args != NULL)
	{	
		ft_print_args(args);
		ft_putchar_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

void	ft_print_args(char *args)
{
	while (args != NULL)
	{
		ft_putstr_fd(args, STDOUT_FILENO);
		args++;
		if (args != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

// int	main(int argc, char **argv)
// {
// 	ft_echo(argv);
// }