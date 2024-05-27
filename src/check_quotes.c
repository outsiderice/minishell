/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 13:22:51 by amagnell         ###   ########.fr       */
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

//checks that there's no open quotes
int	ft_check_quotes(const char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if ((qt_len = ft_quote_len(&line[i], line[i])) == -1)
				(printf("open quotes\n")); //change for ft_error and new prompt line
			i = i + qt_len;
		}
		else
			i++;
	}
	return (0);
}
