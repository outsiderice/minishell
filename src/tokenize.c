/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 14:53:15 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h>
#include "check_input.h"

//skips unquoted spaces
int	ft_space_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	return (i);
}
int	ft_isoperator(char *line, t_tokens *tok)
{
	int	i;

	i = 1;
	if (line[0] == line[1])
		i = 2;
	ft_addtok(&tok, &*line, i);
	return (i);
}
int	ft_isword(char *line, t_tokens *tok)
{
	int	i;
	
	i = 0;
	while (line[i] && ft_ismetachar(line[i]) == 0)
		i++;
	ft_addtok(&tok, &*line, i);
	return (i);
}
void	ft_get_toks(const char *line, t_tokens *tok)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = i + ft_quote_len(&line[i], line[i]);
		else if (line[i] == ' ' || line[i] == '	')
			i = i + ft_space_len(&line[i]);
		else if (line[i] == '<' || line[i] == '>')
			i = i + ft_isoperator(&line[i], tok);
		else
			i = i + ft_isword(&line[i], tok);
	}
}


void	ft_tokenize(const char *line)
{
	t_tokens	tok;

	ft_init_tokens(&tok);
	ft_get_toks(line, &tok);
}
