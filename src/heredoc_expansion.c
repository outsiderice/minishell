/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:18:17 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/30 16:28:53 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_strings(char *str1, char *str2, char *str3, int stat)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (stat);
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
	if (!start)
		exit(-1);
	end = ft_substr(line, end_start, ft_strlen(line) - end_start);
	if (!end)
		exit(free_strings(start, NULL, NULL, -1));
	updated_line = all_join(start, content, end);
	if (!updated_line)
		exit(free_strings(start, end, NULL, -1));
	free_strings(start, end, NULL, 0);
	return (updated_line);
}

char	*expand_line(t_ms *ms, t_env *env_var, char *line)
{
	char	*var_name;
	char	*content;
	char	*updated_line;
	int		i;

	i = 0;
	if (!ft_strchr(line, '$'))
		return (line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			var_name = get_var_name(line, i);
			env_var = find_env_var(env_var, var_name);
			content = get_dollar_content(ms, env_var, var_name);
			i = i + ft_strlen(content);
			updated_line = update_hline(line, content, i);
			free_strings(var_name, content, NULL, 0);
		}
		i++;
	}
	return (updated_line);
	}
	