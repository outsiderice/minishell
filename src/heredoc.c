/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/24 13:05:56 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_end_of_heredoc(t_tokens *eof)
{
	char	*h_end;

	h_end = NULL;
	if (!ft_strchr(eof, '"') && !ft_strchr(eof, '\''))
		h_end = ft_strdup(eof->tok);
	else
	{
		if (expand_quotes(eof) == 1)
			return (NULL);
		h_end = ft_strdup(eof->tok);
	}
	if (!h_end)
		return (NULL);
	return (h_end);
}

expand_line(t_ms *ms, char *line)
{
	char	*updated_line;
	char	*dollar;
	char	*var_name;
	t_env	*env;

	var_name = NULL;
	updated_line = NULL;
	dollar = NULL;
	env = ms->env;
	while (line)
	{
		doll = ft_strchr(line, '$');
		if (doll)
		{
			var_name = get_var_name(doll, 0);
			env_var = find_env_var(env, var_name);
		}
	}
	//find env var
	//set content
	//
	return (updated_line);
}

int	fill_heredoc(t_ms *ms, char *line, t_tokens *eof)
{
	char	*h_end;

	h_end = set_end_of_heredoc(eof);
	if (!h_end)
		return (-1);
	while (line && ft_str_compare(h_end, line) == 1)
	{
		if (!ft_strchr(eof, '"') && !ft_strchr(eof, '\''))
			line = expand_line(ms, line);
		ft_putstr_fd(line, fd[1]);
	}
}

void	close_heredoc(int *fd)
{
	close (fd[0]);
	close (fd[1]);
}

int	ft_heredoc(t_ms *ms, t_tokens *eof)
{
	int		fd[2];
	char	*line;
	char	*h_end;

	if (pipe(fd) == -1)
		return (-1);
	while ('h')
	{
		line = readline(">");
		if (!line)
		{
			close_heredoc(fd);
			return (-1);
		}
		fd[0] = fill_heredoc(t_ms *ms, line, eof);
		if (fd[0] == -1)
		{
			close_heredoc(fd);
			return (-1);
		}
	}
	close(fd[1]);
	return (fd[0]);
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
			fd = ft_heredoc(ms, tok->next);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
