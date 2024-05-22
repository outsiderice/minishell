/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/22 15:20:52 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h>
#include "check_input.h"

//skips unquoted spaces
int	ft_space_len(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	printf("space len is %d\n", i);
	return (i);
}

int	ft_isoperator(const char *line, t_tokens **tokens)
{
	int	i;

	i = 1;
	if (line[0] == line[1])
		i = 2;
	ft_addtok(&*line, i, tokens);
	return (i);
}

int	ft_isword(const char *line, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (line[i] && ft_ismetachar(line[i]) == 0)
		i++;
	ft_addtok(&*line, i, tokens);
	return (i);
}

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

void	ft_tokenize(const char *line)
{
	t_tokens	*tokens;
	t_tokens	*temp;
	
	tokens = NULL;
	printf("1 where\n");
	ft_get_toks(line, &tokens);
	printf("2 where\n");
	while (tokens != NULL)
	{
		printf("token stored is <%s>\n", tokens->token);
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}
