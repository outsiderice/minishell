/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 13:02:58 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//adds a new token to the end of the list
void	ft_tok_addback(t_tokens **tokens, t_tokens *new_tok)
{
	t_tokens	*temp;

	temp = *tokens;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_tok;
}

//adds a new token to the tokens list
void	ft_addtok(const char *line, int len, t_tokens **tokens)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
	{
		printf("bad malloc\n");
		return ; //add proper protection later
	}
	if (ft_ismetachar(*line) == 3)
		new_tok->type = 2;
	else
		new_tok->type = 1;
	new_tok->tok = ft_substr(line, 0, len);
	new_tok->next = NULL;
	if (*tokens == NULL)
		*tokens = new_tok;
	else
		ft_tok_addback(tokens, new_tok);
}

//checks if c is a metacharacter
//returns a number depending on which type or 0 if it isn't
int	ft_ismetachar(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	if (c == '|')
		return (2);
	if (c == ' ' || c == '	')
		return (3);
	if (c == '<' || c == '>')
		return (4);
	return (0);
}
