/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:03:14 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 12:50:45 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <unistd.h>

t_tokens	*ft_addtok(char *line, int len);
{
	
}

void	ft_init_tokens(t_tokens *tok)
{
	tok->type = 0;
	tok->token = NULL;
	tok->next = NULL;
}