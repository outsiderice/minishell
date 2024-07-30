/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/30 15:04:25 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	set_end_of_heredoc(t_tokens *eof)
{
	if (!ft_strchr(eof->tok, '"') && !ft_strchr(eof->tok, '\''))
		return (EXIT_SUCCESS);
	else
	{
		if (expand_quotes(eof) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*update_hline(char *line, char *content, int i)
{
	char	*updated_line;
	char	*start;
	char	*end;
	int		end_start;

	updated_line = NULL;
	start = NULL;
	end = NULL;
	end_start = ft_strlen(content) + i;
	start = ft_substr(line, 0, i);
	end = ft_substr(line, end_start, ft_strlen(line) - end_start);
	updated_line = all_join(start, content, end);
	free(start);
	free(end);
	return (updated_line);
}


char	*expand_line(t_ms *ms, char *line)
{
	t_env	*env_var;
	char	*var_name;
	char	*content;
	char	*updated_line;
	int		i;

	i = 0;
	env_var = ms->env;
	if (!ft_strchr(line, '$'))
		return (line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			var_name = get_var_name(line, i);
			env_var = find_env_var(env_var, var_name);
			content = get_dollar_content(ms, env_var, var_name);
			free (var_name);
			free (env_var);
			updated_line = update_hline(line, content, i);
			free (content);
			i = i + ft_strlen(content);
		}
		i++;
	}
	return (updated_line);
	}

void	fill_hd(t_ms *ms, char *line, int expansion, int hd)
{
	if (expansion == 1)
		line = expand_line(ms, line);
	ft_putstr_fd(line, hd);
	write(hd, "\n", 1);
}
	

int	open_heredoc(t_ms *ms, char *h_end, int hd, int expansion)
{
	char	*line;

	while (42)
	{
		line = readline(">");
		if (!line)
			exit(close(hd));
		if (ft_str_compare(line, h_end) == 0)
		{
			free(line);
			break;
		}
		else if (*line != '\0')
			fill_hd(ms, line, expansion, hd);
		free (line);
		line = NULL;
	}
	free_env(&ms->env);
	exit (close(hd));
}

int	ft_heredoc(t_ms *ms, t_tokens *eof, int expansion)
{
	pid_t		pid;
	int			status;
	int			hd[2];

	if (set_end_of_heredoc(eof) == 1)
		return (-1);
	if (pipe(hd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(hd[0]);
		ft_start_signals(2);
		ft_ignoresig(SIGQUIT);
		open_heredoc(ms, eof->tok, hd[1], expansion);
	}
	waitpid(pid, &status, 0);
	close(hd[1]);
	return (hd[0]);
}

//iterates tokens, if it finds a heredoc operator it calls open_heredoc
int	handle_heredocs(t_ms *ms)
{
	int			fd;
	int			expansion;
	t_tokens	*tok;

	fd = -2;
	tok = ms->tokens;
	while(tok)
	{
		expansion = 1;
		ft_ignoresig(SIGQUIT);
		if (tok->type == 4)
		{
			if (ft_strchr(tok->next->tok, '\'') || ft_strchr(tok->next->tok, '"'))
				expansion = 0;
			if (fd && fd != -2)
					close(fd);
			fd = ft_heredoc(ms, tok->next, expansion);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	ft_start_signals(1);
	return(fd);
}
