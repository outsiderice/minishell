/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/22 15:41:29 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>
#include "../lib/libft/include/libft.h"
#include <stdio.h> //for printf, delete later

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

	printf("adding new tok\n");
	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
	{
		printf("bad malloc\n");
		return ; //add proper protection later
	}
	if (ft_ismetachar(*line) == 0)
		new_tok->type = 1;
	else
		new_tok->type = 2;
	new_tok->token = ft_substr(line, 0, len);
	new_tok->next = NULL;
	printf("after new_tok values assignment\n");
	if (*tokens == NULL)
		*tokens = new_tok;
	else
	{
		printf("*tokens is not empty\n");
		temp = *tokens;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_tok;
	}
	printf("new tok added\n");
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
