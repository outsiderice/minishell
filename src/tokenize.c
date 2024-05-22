/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/22 17:50:16 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h> // for test printf
#include "check_input.h"

//skips unquoted spaces and returns the len of spaces
int	ft_space_len(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	printf("space len is %d\n", i);
	return (i);
}

//checks if it's <, <<, > or >> and saves it to the token struct
//returns the len of the operator.
int	ft_isoperator(const char *line, t_tokens **tokens)
{
	int	i;

	i = 1;
	if (line[0] == line[1])
		i = 2;
	ft_addtok(&*line, i, tokens);
	return (i);
}

//saves the word to the token struct and returns it's len
int	ft_isword(const char *line, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (line[i] && ft_ismetachar(line[i]) == 0)
		i++;
	ft_addtok(&*line, i, tokens);
	return (i);
}

//iterates input line and saves the tokens to the token struct
void	ft_get_toks(const char *line, t_tokens **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = i;
			i = i + ft_quote_len(&line[i], line[i]);
			ft_addtok(&line[j], i - j, tokens);
		}
		else if (line[i] == ' ' || line[i] == '	')
			i = i + ft_space_len(&line[i]);
		else if (line[i] == '<' || line[i] == '>')
			i = i + ft_isoperator(&line[i], tokens);
		else
			i = i + ft_isword(&line[i], tokens);
	}
}

//separates each token into a node in list tokens and assigns a type
void	ft_tokenize(const char *line)
{
	t_tokens	*tokens;
	t_tokens	*temp;

	tokens = NULL;
	ft_get_toks(line, &tokens);
	while (tokens != NULL)		//while to check what's saved is correct
	{
		printf("token stored is <%s>\n", tokens->token);
		printf("token type is %d\n", tokens->type);
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}
