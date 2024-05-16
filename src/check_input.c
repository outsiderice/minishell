/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 10:34:43 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_input.h"
# include "../lib/libft/include/libft.h"
# include <stdlib.h>

//Check quotes and store the info needed to split them as a pack later.
//Also store the type, wheteher they're " or '

// ft_check_pipes(char *line)
// {
// 	//if there's pipes make a first split and start the whole pipe process
// 	//if there's no pipes do 2nd split by spaces
// }

int	ft_quote_len(char *line, char type, int start)
{
	int	i;

	i = 0;
	start++;
	while (line[start] && line[start] != type)
	{
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

int	ft_check_quotes(char *line)
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

int	ft_check_input(char *line)
{
	ft_check_quotes(line);
	// ft_check_pipes(line);
	return (EXIT_SUCCESS);
}