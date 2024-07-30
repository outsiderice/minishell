/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:18:17 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/30 15:46:17 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_strings(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
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
			free(var_name);
			free(content);
			//free(env_var);
		}
		i++;
	}
	return (updated_line);
	}
	