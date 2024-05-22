/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/22 10:06:00 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>
#include "../lib/libft/include/libft.h"

// void	ft_init_tokens(t_tokens **tokens)
// {
// 	t_tokens *tok;
	
// 	tok->type = 0;
// 	tok->token = NULL;
// 	tok->next = NULL;
// }

void	ft_addtok(const char *line, int len, t_tokens **tokens)
{
	t_tokens	*new_tok;
	t_tokens	*temp;

	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
		return ; //add proper protection later
	if (ft_ismetachar(*line) == 0)
		new_tok->type = 1;
	else
		new_tok->type = 2;
	new_tok->token = ft_substr(line, 0, len);
	new_tok->next = NULL;
	if (*tokens == NULL)
		*tokens = new_tok;
	else
	{
		temp = *tokens;
		while (temp != NULL)
			temp = temp->next;
		temp->next = new_tok;
	}
}

int	ft_ismetachar(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	if (c == ' ' || c == '	')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
