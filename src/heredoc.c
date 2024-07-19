/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/19 12:54:44 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_end_of_heredoc(char *tok)
{}

int	open_heredoc(char *eof)
{
	int	fd;
}

int	handle_heredocs(t_ms *ms)
{
	int			fd;
	t_tokens	*tok;
	char		*eof;

	fd = -2;
	eof = NULL;
	tok = ms->tokens;
	while(tok)
	{
		if (tok->type == 4)
		{
			if (fd && fd != -2)
				close(fd);
			eof = get_end_of_heredoc(tok->next->tok);
			if (!eof)
				return (-1); //maybe another value?
			fd = open_heredoc(eof);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
