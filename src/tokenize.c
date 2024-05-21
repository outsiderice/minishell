/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 09:21:08 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h>

void	ft_init_tokens(t_tokens *tok)
{
	tok->type = 0;
	tok->token = NULL;
	tok->next = NULL;
}
char	ft_isspace(char c)
{
	if (c == ' ' || c == '	')
		return (c);
	return ((char)NULL);
}

void	ft_tokenize(const char *line)
{
	t_tokens	tok;

	ft_init_tokens(&tok);
	return ;
}
