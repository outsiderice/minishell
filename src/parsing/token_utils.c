/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/12 12:38:44 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if c is a metacharacter
//returns a number depending on which type or 0 if it isn't
int	ft_ismetachar(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	if (c == '|')
		return (2);
	if (c == '<' || c == '>')
		return (3);
	if (c == ' ' || c == '	')
		return (4);
	return (0);
}

//skips unquoted spaces and returns the len of spaces
int	ft_space_len(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	return (i);
}

//returns the len of the operator
int	ft_isoperator(const char *line)
{
	int	i;

	i = 1;
	if (line[0] == '|')
		return (i);
	if (line[0] == line[1])
		i = 2;
	return (i);
}

//returns the len of the word
int	ft_isword(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_ismetachar(line[i]) == 0)
		i++;
	return (i);
}
