/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 17:18:03 by amagnell         ###   ########.fr       */
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

int	ft_quote_len(const char *line, char type)
{
	int	i;

	i = 1;
	ft_printf("		%s\n", line);
	while (line[i] && line[i] != type)
	{
		ft_printf("		string is at %d and i is %d\n", i, i);
		ft_printf("%c\n", (char) line[i]);
		i++;
	}
	if (line[i] == type)
	{
		i++;
		return (i);
	}
	ft_printf("		char is %c and i is %d\n", line[i], i);
	ft_printf("		error\n");
	exit (EXIT_FAILURE);
}

int	ft_check_quotes(const char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	ft_printf("i = %d\n", i);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt_len = ft_quote_len(&line[i], line[i]);
			i = i + qt_len;
			ft_printf("i is now %d\n", i);
		}
		else
			i++;
		ft_printf("i is %d\n", i);
	}
	return (0);
}

int	ft_check_input(const char *line)
{
	ft_check_quotes(line);
	ft_check_pipes(line);
	return (EXIT_SUCCESS);
}