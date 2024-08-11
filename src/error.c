/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:38:39 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/10 17:53:13 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_error(t_ms **ms, char *line)
// {
// 	if ((*ms)->exitstatus == 2)
// 	{
// 		printf("eggshell: syntax error near unexpected token\n");
// 		free(line);
// 		return ;
// 	}
// }

// Pass two strings to give a personalized error msg
// Returns 1
int	error_msg(char *msg, char *deets)
{
	ft_putstr_fd("eggshell: ", 2);
	ft_putstr_fd(msg, 2);
	if (deets)
		ft_putstr_fd(deets, 2);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	error_msg2(char *msg, char *deets, char *deets2, int nl)
{
	ft_putstr_fd(msg, 2);
	if (deets)
		ft_putstr_fd(deets, 2);
	if (deets2)
		ft_putstr_fd(deets2, 2);
	if (nl == 1)
		ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
