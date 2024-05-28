/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/28 17:49:15 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//stores the token and it's type to the struct
//returns the token len
int	ft_complex_tok(const char *line)
{
	int i;
	int	end;

	i = 0;
	end = 0;
	while (end == 0)
	{
		//goes until the end of the token
		if (ft_ismetachar(line[i]) != 1 && ft_ismetachar(line[i]) != 0)
			end = 1;
	}
	return (i);
}

//gets the len and type of the token and stores it to the struct
//when a token could be complex it delegates to ft_complex_token
//returns the len of the latest token
int	ft_get_tok(const char *line, t_tokens **tokens)
{
	int	i;

	i = 0;
	if (line[i] == '"' || line[i] == '\'')
		i = ft_complex_tok(&line[i]);
	else if (ft_ismetachar(line[i]) == 2)
	{
		i = ft_isoperator(&line[i]);
		ft_addtok(&line[0], i, 2, tokens);
	}
	else if (ft_ismetachar(line[i]) == 3)
	{
		i = ft_isoperator(&line[i]);
		ft_addtok(&line[0], i, 3, tokens);
	}
	else
		i = ft_complex_tok(&line[i]);
	return (i);
}

//skips spaces and the rest gets stored as a token
//calls for expansion check
//and calls ft_parse
void	ft_tokenize(const char *line, t_ms *ms)
{
	t_tokens	*toks;
	int			i;

	i = 0;
	toks = NULL;
	while (line[i])
	{
		if (ft_ismetachar(line[i]) < 4)
			i = i + ft_get_tok(&line[i], &toks);
		else
			i = i + ft_space_len(&line[i]);
	}
	ms->tokens = toks;
	// ft_expansion_check(ms);
	// ft_parse(ms);
}
