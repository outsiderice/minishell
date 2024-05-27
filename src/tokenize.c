/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 14:57:14 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	ft_isoperator(const char *line, t_tokens **tokens)
{
	int	i;

	i = 1;
	if (line[0] == line[1])
		i = 2;
	return (i);
}

//saves the word to the token struct and returns it's len
int	ft_isword(const char *line, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (line[i] && ft_ismetachar(line[i]) == 0)
		i++;
	return (i);
}

//gets the len of the token and stores it to the struct
//returns the len of the latest token
int	ft_get_toks(const char *line, t_tokens **tokens)
{
	int	i;

	i = 0;
	if (line[i] == '"' || line[i] == '\'')
	{
		i = ft_quote_len(&line[i], line[i]);
		ft_addtok(&line[0], i, tokens);
	}
	else if (ft_ismetachar(line[i]) == 2 || ft_ismetachar(line[i]) == 3)
	{
		i = ft_isoperator(&line[i], tokens);
		ft_addtok(&line[0], i, tokens);
	}
	else
	{
		i = ft_isword(&line[i], tokens);
		ft_addtok(&line[0], i, tokens);
	}
	return (i);
}

//skips spaces and the rest gets stored as a token
void	ft_tokenize(const char *line, t_ms *ms)
{
	t_tokens	*toks;
	int			i;

	i = 0;
	toks = NULL;
	while (line[i])
	{
		if (ft_ismetachar(line[i]) < 4)
			i = i + ft_get_toks(&line[i], toks);
		else
			i = i + ft_space_len(&line[i]);
	}
	ms->tokens = toks;
	//ft_parse(tokens);
}
