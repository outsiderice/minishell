/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/24 15:16:27 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_end_of_heredoc(t_tokens *eof)
{
	char	*h_end;

	h_end = NULL;
	if (!ft_strchr(eof->tok, '"') && !ft_strchr(eof->tok, '\''))
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

// expand_line(t_ms *ms, char *line)
// {
// 	char	*updated_line;
// 	char	*dollar;
// 	char	*var_name;
// 	t_env	*env;

// 	var_name = NULL;
// 	updated_line = NULL;
// 	dollar = NULL;
// 	env = ms->env;
// 	while (line)
// 	{
// 		doll = ft_strchr(line, '$');
// 		if (doll)
// 		{
// 			var_name = get_var_name(doll, 0);
// 			env_var = find_env_var(env, var_name);
// 		}
// 	}
// 	//find env var
// 	//set content
// 	//
// 	return (updated_line);
// }

// int	fill_heredoc(int *fd, t_ms *ms, char *line, t_tokens *eof)
// {
	
// 	(void)ms; //delete

// 	h_end = set_end_of_heredoc(eof);
// 	if (!h_end)
// 		return (-1);
// 	while (line && ft_str_compare(h_end, line) == 1)
// 	{
// 		//if (!ft_strchr(eof, '"') && !ft_strchr(eof, '\''))
// 		//	line = expand_line(ms, line);
// 		ft_putstr_fd(line, fd[1]);
// 	}
// 	return (fd[1]);
// }

int	close_heredoc(int *fd, int err)
{
	close (fd[0]);
	close (fd[1]);
	if (err == 1)
		return (-1);
	return (0);
}
// char	*h_prompt(int *fd)
// {
// 	char	*line;
// }

int	ft_heredoc(t_ms *ms, t_tokens *eof, char *h_end)
{
	int		fd[2];
	char	*line;
	(void)eof;
	(void)ms;

	if (pipe(fd) == -1)
		return (-1);
	while (42)
	{
		line = readline(">");
		if (!line)
			return(close_heredoc(fd, 1));
		if (ft_str_compare(line, h_end) == 0)
			break;
		//line = expand_line();
		ft_putstr_fd(line, fd[1]);
		write(fd[1], "\n", 1);
		free (line);
		line = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}

//iterates tokens, if it finds a heredoc operator it calls open_heredoc
int	handle_heredocs(t_ms *ms)
{
	int			fd;
	t_tokens	*tok;
	char		*h_end;

	fd = -2;
	tok = ms->tokens;
	while(tok)
	{
		if (tok->type == 4)
		{
			if (fd && fd != -2)
				close(fd);
			h_end = set_end_of_heredoc(tok->next);
			fd = ft_heredoc(ms, tok->next, h_end);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
