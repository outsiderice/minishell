/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 14:04:52 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_input.h"
# include "../lib/libft/include/libft.h"
# include <stdlib.h>
# include "lexer.h"

//Check quotes and store the info needed to split them as a pack later.
//Also store the type, wheteher they're " or '

void	ft_check_pipes(const char *line)
{
	// while (*line != '|')
	// 	line++;
	// if (*line == '|')
	// 	pipe_syntax(line);
	ft_lexer(line);
}

int	ft_quote_len(const char *line, char type, int start)
{
	int	i;

	i = 0;
	start++;
	// ft_printf("%s", line);
	while (line[start] && line[start] != type)
	{
		ft_printf("%c\n", (char) line[start]);
		start++;
		i++;
	}
	if (line[start] == type)
	{
		i++;
		return (i);
	}
	ft_printf("error\n");
	exit (EXIT_FAILURE);
}

int	ft_check_quotes(const char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt_len = ft_quote_len(&line[i], line[i], i);
			i = i + qt_len;
		}
		i++;
	}
	return (0);
}

int	ft_check_input(const char *line)
{
	ft_check_quotes(line);
	// ft_check_pipes(line);
	return (EXIT_SUCCESS);
}