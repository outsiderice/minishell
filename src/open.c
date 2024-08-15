/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:57:13 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/15 09:58:15 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input(char *tok, char *file, t_args *args, t_ms *ms)
{
	if (ft_strlen(tok) == 1)
	{
		args->fd[0] = open(file, O_RDONLY);
		args->i_file = file;
	}
	else
	{
		args->fd[0] = ms->heredoc;
		args->redir_type = 2;
	}
}

void	open_output(char *tok, char *file, t_args *args)
{
	if (ft_strlen(tok) == 1)
	{
		args->fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		args->fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	args->o_file = file;
}
