/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:53 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/06 14:36:30 by amagnell         ###   ########.fr       */
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
	printf("inside qte len\n");
	while (line[i] && line[i] != type)
	{
		printf("qte_len, before i++, i =%d\n", i);
		i++;
	}
	printf("found the 0 or another quote\n");
	if (line[i] == type)
	{
		printf("i++ for the ending quote\n");
		i++;
		printf("qte_len-> i returned =%d\n", i);
		return (i);
	}
	printf("the quotes are open\n");
	return (-1);
}

//checks that there's no open quotes
void	ft_check_quotes(const char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	printf("ft_check quotes\n");
	while (line[i] != '\0')
	{
		printf("ft_check quotes->inside line loop\n");
		if (line[i] == '"' || line[i] == '\'')
		{
			printf("ft_check quotes->has found a quote character\n");
			qt_len = ft_quote_len(&line[i], line[i]);
			if (qt_len == -1)
			{
				(printf("ERROR: open quotes\n")); //change for ft_error and new prompt line
			}
			printf("ft_check quotes->before adding qt_len to i, i = %d\n", i);
			i = i + qt_len;
			printf("ft_check quotes->added qt_len to i, i = %d\n", i);
		}
		else
		{
			printf("ft_check quotes->line[i] is not a quote, i++\n");
			i++;
		}
	}
	return ;
}
