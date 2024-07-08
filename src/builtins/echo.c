/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/08 23:30:13 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//echo -n "hola" "hola"
//echo with no argument print \n
// echo -n with with no arguments just shows the next line
// how to check for unexpected error for 1
// implement -n -nnnnnnnn and etc

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

int	ft_echo(t_args *args)
{
	int	do_jump;
	char **argv;

	argv = args->argv;
	argv++;
	do_jump = ft_n_check(*argv);
	while (ft_n_check(*argv) == 1)
		argv++;
	ft_print_args(argv, args->fd[1]);
	if (do_jump == 0)
		ft_putchar_fd('\n', args->fd[1]);
	return (0);
}
/*
 int	main(int ac, char **av)
{
	char	**args;
	int		i;
	int		x;
	int 	j;
	
	if (ac < 2)
		return (0);
	args = malloc(sizeof(char *) * ac);
	if (!args)
		return (0);
	i = 1;
	x = 0;
	while (i < ac)
	{
		args[x] = strdup(av[i]);
		if (!args[x])
		{
			j = 0;
			while (j < x)
			{
				free(args[j]);
				j++;
			}
			free(args);
			return (0);
		}
		//printf("%s\n", args[x]);
		i++;
		x++;
	}
	args[x] = NULL;
 	ft_echo(args);
	j = 0;
	while (args[j] != NULL)
    {
        free(args[j]);
		j++;
    }
    free(args);
	return (1);
}*/