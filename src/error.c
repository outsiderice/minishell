/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:38:39 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_ms **ms, char *line)
{
	if ((*ms)->exitstatus == 2)
	{
		printf("eggshell: syntax error near unexpected token\n");
		free(line);
		return ;
	}
}
