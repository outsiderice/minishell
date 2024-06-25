/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:44 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/21 13:54:03 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/minishell.h"
#include "../../lib/libft/include/libft.h"
#include <string.h>
#include <limits.h>

/* Cntol C and exit can be the same?????
	function to free the minishell struct
	function to free the t_env list
	call the function to free the t_arg list
	function to exit status
*/

int is_numeric(char *str) 
{
    if (!str || *str == '\0')
        return (0);
    if (*str == '-' || *str == '+')
        str++;
    while (*str) 
	{
        if (*str < '0' || *str > '9') 
            return (0);
        str++;
    }
    return (1);
}


int ft_atoi_long_long(char *str)
{
	long long int	res;
	int				sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res*sign);
}

int	ft_check_lli(char *str)
{
	unsigned long long int	res;
	int						sign;

	if (is_numeric(str) == 0 || ft_strlen(str) > 20)
		return (0);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = ft_atoi_long_long(str);
	if (sign == -1 && res - 1 <= LONG_MAX)
		return(1);
	else if (sign == 1 && res <= LONG_MAX)
		return (1);
	return(0);
}

int	ft_args_len(char **args)
{
	int	len;

	len = 0;
	while (args[len] != NULL)
		len++;
	return (len);
}
// deberia de hacer frees en algun momento
//tiene que aceptar ms comoa rgumento
int	ft_exit(char **args) //possibly save the readline history
{
	long long int	exit_status;
	int	args_len;

	exit_status = 0;
	args++;
	args_len = ft_args_len(args);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_check_lli(*args) == 0)
	{
		//exit(0);
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(*args, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		return(0);
	}
	if (args_len > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (0);
	}
	exit_status = ft_atoi_long_long(*args);
	//ft_free_ms(ms);
	//exit(exit_status);
	return (1);
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
 	ft_exit(args);
	j = 0;
	while (args[j] != NULL)
    {
        free(args[j]);
		j++;
    }
    free(args);
	return (1);
}*/