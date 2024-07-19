/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/19 13:41:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_end_of_heredoc(char *eof)
{

}

int	open_heredoc(char *eof)
{
	int		fd;
	char	*line;
	char	*end;

	end = set_end_of_heredoc(eof);
	line = readline(">");
	while (line && ft_str_compare(end, line) == 1)
	{
		ft_putstr_fd(line, fd);
	}
}

int	handle_heredocs(t_ms *ms)
{
	int			fd;
	t_tokens	*tok;

	fd = -2;
	tok = ms->tokens;
	while(tok)
	{
		if (tok->type == 4)
		{
			if (fd && fd != -2)
				close(fd);
			fd = open_heredoc(tok->next->tok);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
