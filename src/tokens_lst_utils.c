/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:01:59 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/18 13:20:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// deletes tok
void	del_tok(t_tokens **lst, t_tokens *tok)
{
	t_tokens	*to_del;
	t_tokens	*prev;

	to_del = *lst;
	while (to_del != NULL && to_del != tok)
	{
		prev = to_del;
		to_del = to_del->next;
	}
	if (to_del == NULL)
		return ;
	if (prev == NULL)
		*lst = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del);
}

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
void	ft_addtok(const char *line, int len, int type, t_tokens **tokens)
{
	t_tokens	*new_tok;

	new_tok = malloc(sizeof(t_tokens) * 1);
	if (!new_tok)
	{
		printf("bad malloc\n");
		return ; //add proper protection later
	}
	new_tok->type = type;
	new_tok->tok = ft_substr(line, 0, len);
	new_tok->next = NULL;
	if (*tokens == NULL)
		*tokens = new_tok;
	else
		ft_tok_addback(tokens, new_tok);
}