/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 11:13:58 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_input.h"
#include "../lib/libft/include/libft.h"
#include <stdlib.h>
#include "tokens.h"

//Check quotes and store the info needed to split them as a pack later.
//Also store the type, wheteher they're " or '

void	ft_check_pipes(const char *line)
{
	// while (*line != '|')
	// 	line++;
	// if (*line == '|')
	// 	pipe_syntax(line);
	ft_tokenize(line);
}

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
	exit (EXIT_FAILURE); //change for error and new prompt line
}

int	ft_check_quotes(const char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	//ft_printf("i = %d\n", i); //test
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt_len = ft_quote_len(&line[i], line[i]);
			i = i + qt_len;
			//ft_printf("i is now %d\n", i); //test
		}
		else
			i++;
		//ft_printf("i is %d\n", i); //test
	}
	return (0);
}

int	ft_check_input(const char *line)
{
	ft_check_quotes(line);
	ft_check_pipes(line);
	//ft_printf("out\n"); //test
	return (EXIT_SUCCESS);
}
