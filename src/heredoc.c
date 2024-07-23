/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/23 14:30:45 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_end_of_heredoc(char *eof)
{
	char	*h_end;

	h_end = NULL;
	if (!ft_strrchr(eof, '"') && !ft_strchr(eof, '\''))
	{
		h_end = ft_strdup(eof);
		if (!h_end)
			return (NULL);
	}
	else
	{
		//remove quotes of eof as needed
	}
	return (h_end);
}

int	fill_heredoc()
{
	while (line && ft_str_compare(h_end, line) == 1)
	{
		if (!ft_strrchr(eof, '"') && !ft_strchr(eof, '\''))
			//expand line
		ft_putstr_fd(line, fd[1]);
	}
}

int	ft_heredoc(char *eof)
{
	int		fd[2];
	char	*line;
	char	*h_end;

	if (pipe(fd) == -1)
		return (-1);
	h_end = set_end_of_heredoc(eof);
	line = readline(">");
	if (!line)
	{
		close (fd[1]);
		close (fd[0]);
		free(h_end);
		return (-1);
	}
	fd[0] = fill_heredoc();
	close(fd[1]);
	return (fd[0])
}

//iterates tokens, if it finds a heredoc operator it calls open_heredoc
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
			fd = ft_heredoc(tok->next->tok);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
