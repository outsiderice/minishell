/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:03 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/27 16:37:47 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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
	updated_line = NULL;
	if (!ft_strchr(line, '$'))
		return (line);
	while (line[i])
	{
		printf("am i stuck?\n");
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
	if (updated_line != NULL)
		printf("expanded line = <%s>\n", updated_line);
	return (updated_line);
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
		{
			if (expansion == 1)
				line = expand_line(ms, line);
			ft_putstr_fd(line, hd);
			write(hd, "\n", 1);
		}
		free (line);
		line = NULL;
	}
	close(hd);
	free_env(&ms->env);
	exit (0);
}

int	ft_heredoc(t_ms *ms, t_tokens *eof, int expansion)
{
	pid_t		pid;
	char		*h_end;
	int			status;
	int			hd[2];

	h_end = set_end_of_heredoc(eof);
	if (!h_end)
		return (-1);
	if (pipe(hd) == -1)
		exit (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_start_signals(2);
		open_heredoc(ms, h_end, hd[1], expansion);
	}
	waitpid(pid, &status, 0); //use status?
	if (h_end)
		free (h_end);
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
	expansion = 1;
	while(tok)
	{
		ft_ignoresig(SIGQUIT);
		if (tok->type == 4)
		{
			if (!(ft_strchr(tok->next->tok, '\'') || ft_strchr(tok->next->tok, '"')))
				expansion = 0;
			if (fd && fd != -2)
					close(fd);
			printf("expansion = %d\n", expansion);
			fd = ft_heredoc(ms, tok->next, expansion);
			if (fd == -1)
				return (-1);
		}
		tok = tok->next;
	}
	return(fd);
}
