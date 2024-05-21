/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 15:30:47 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

void	ft_init_tokens(t_tokens *tok)
{
	tok->type = 0;
	tok->token = NULL;
	tok->next = NULL;
}

t_tokens	*ft_addtok(t_tokens *tok, char *line, int len)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
		return (NULL); //add proper protection later
	new_tok->type = ;
	return (new_tok);
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
