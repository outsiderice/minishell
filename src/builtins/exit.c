/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:44 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/09 19:19:23 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_atoi_long_long(char *str)
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
	return (res * sign);
}

int	ft_check_lli(char *str)
{
	unsigned long long int	res;
	int						sign;

	res = 0;
	sign = 1;
	if (is_numeric(str) == 0 || ft_strlen(str) > 20)
		return (0);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = ft_atoi_long_long(str);
	if (sign == -1 && res - 1 <= LONG_MAX)
		return (1);
	else if (sign == 1 && res <= LONG_MAX)
		return (1);
	return (0);
}

void	exit_msg(char *args)
{
	ft_putstr_fd("eggshell: exit: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return;
}

int	ft_exit(t_ms *ms, char **args)
{
	long long int	exit_status;
	int				args_len;

	exit_status = 0;
	args_len = ft_args_len(args);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args_len > 1)
	{
		args++;
		if (ft_check_lli(*args) == 0)
		{
			exit_msg(*args);
			exit_status = 255;
		}
		else
			exit_status = ft_atoi_long_long(*args);
	}
	if (args_len > 2)
	{
		error_msg("exit: too many arguments", NULL);
		return (1);
	}
	free_ms(&ms);
	exit(exit_status % 256);
}
