/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:01:59 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/08 14:58:14 by amagnell         ###   ########.fr       */
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

//adds a new token to the tokens list return 0 or -1 if it fails
int	ft_addtok(const char *line, int len, int type, t_tokens **tokens)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
		return (-1);
	new_tok->type = type;
	new_tok->tok = ft_substr(line, 0, len);
	new_tok->next = NULL;
	if (*tokens == NULL)
		*tokens = new_tok;
	else
		ft_tok_addback(tokens, new_tok);
	return (0);
}
