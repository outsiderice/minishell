/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/24 12:19:11 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//stores the token and it's type to the struct
//returns the token len or -1 if allocation fails
int	ft_complex_tok(const char *line, t_tokens **tokens)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (end == 0 && line[i])
	{
		if (ft_ismetachar(line[i]) == 1)
			i = i + ft_quote_len(&line[i], line[i]);
		else
			i = i + ft_isword(&line[i]);
		if (ft_ismetachar(line[i]) != 1 && ft_ismetachar(line[i]) != 0)
			end = 1;
	}
	end = ft_addtok(&line[0], i, 0, tokens);
	if (end == -1)
		return (-1);
	return (i);
}

//gets the len and type of the token and stores it to the struct
//returns the len of the latest token or -1 if allocation fails
int	ft_get_tok(const char *line, t_tokens **tokens)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (line[i] == '"' || line[i] == '\'')
		i = ft_complex_tok(&line[i], tokens);
	else if (ft_ismetachar(line[i]) == 2)
	{
		i = ft_isoperator(&line[i]);
		check = ft_addtok(&line[0], i, 2, tokens);
	}
	else if (ft_ismetachar(line[i]) == 3)
	{
		i = ft_isoperator(&line[i]);
		check = ft_addtok(&line[0], i, 3, tokens);
	}
	else
		i = ft_complex_tok(&line[i], tokens);
	if (check == -1)
		return (-1);
	return (i);
}

//skips spaces and otherwise fills t_tokens
//returns the length of the token or -1 if allocation fails
int	ft_tokenize(const char *line, t_tokens **toks)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_ismetachar(line[i]) < 4)
		{
			j = ft_get_tok(&line[i], toks);
			if (j == -1)
				return (-1);
			i = i + j;
		}
		else
			i = i + ft_space_len(&line[i]);
	}
	return (i);
}

//checks if there're open quotes and that token allocation went correctly
//returns 1 if it encounters an error or 0 if everything is ok
int	ft_tok_checks(const char *line, t_ms *ms)
{
	t_tokens	*toks;
	int			len;

	len = 0;
	toks = NULL;
	if (!line[0])
		return (EXIT_FAILURE);
	if (ft_check_quotes((const char *)line, ms) != 0)
	{
		error_msg("syntax error near unexpected token,", "open quotes");	
		return (EXIT_FAILURE);
	}
	len = ft_tokenize(line, &toks);
	if (len == -1)
	{
		error_msg("token memory allocation failure\n", NULL);
		return (EXIT_FAILURE);
	}
	ms->tokens = toks;
	//Test to see what tokens are stored
	while (toks->next != NULL)
	{
		printf("\nToken is %s\nType %d\n\n", toks->tok, toks->type);
		toks = toks->next;
	}
	printf("\nToken is %s\nType %d\n\n", toks->tok, toks->type);
	//Test ends here, delete later
	return (0);
}
