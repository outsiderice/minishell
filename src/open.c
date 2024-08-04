/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:57:13 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/04 13:20:16 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input(char *tok, char *file, t_args *args, t_ms *ms)
{
	if (ft_strlen(tok) == 1)
	{
		args->fd[0] = open(file, O_RDONLY);
		args->redir_type = 1;
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
		args->redir_type = 3;
	}
	else
	{
		args->fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		args->redir_type = 4;
	}
}
