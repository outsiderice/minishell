/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/14 19:55:31 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

//echo -n "hola" "hola"
//echo with no argument print \n
// echo -n with with no arguments just shows the next line
// how to check for unexpected error for 1
// implement -n -nnnnnnnn and etc

void	ft_print_args(char **args)
{
	while (args != NULL)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		args++;
		if (args != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	ft_echo(char **args)
{
	args++;
	if (*args == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (ft_str_compare(*args, "-n") == 0)
		ft_print_args(args[i++]);
	else if (args != NULL)
	{	
		ft_print_args(args);
		ft_putchar_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

 int	main(int ac, char **av)
{
	char	**args;
	int		i;
	int		x;
	int		len;

	args = malloc(sizeof(char *) * ac);
	if (!args)
		return (0);
	i = 1;
	x = 0;
	while(i < ac)
	{
		len = strlen(av[i]);
		args[x] = malloc(sizeof(char) * (len + 1));
		if (!args[x])
			return (0); // bueno y free pero es main de mentira :)
		args[x] = strdup(av[i]);
		printf("%s\n", args[x]);
		i++;
		x++;
	}
	args[3] = NULL;
 	ft_echo(args);
	return (1);
}