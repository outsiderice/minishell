/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/21 20:12:22 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//looks for the ending quote of the same type
//if found returns the length of the quoted part, quotes included
//if not found returns -1
int	ft_quote_len(const char *line, char type)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != type)
		i++;
	if (line[i] == type)
	{
		i++;
		return (i);
	}
	return (-1);
}

//checks if there's open quotes, returns 1 if there's open quotes 0 if not
int	ft_check_quotes(const char *line, t_ms *ms)
{
	int	i;
	int	qt_len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt_len = ft_quote_len(&line[i], line[i]);
			if (qt_len == -1)
			{
				ms->exitstatus = 2;
				return (EXIT_FAILURE);
			}
			i = i + qt_len;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
