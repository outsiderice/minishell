/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/30 16:43:29 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the $ which must be expanded
//look for the value and substitute for what's found in env 
//or an empty string if not found
//remove quotes

//find $ signs to be expanded in the tokens
//when a viable $ is found calls ft_expand
void	ft_expansion_check(t_ms *ms)
{
	t_tokens	*current;

	current = ms->tokens;
	while (current->next != NULL)
	{
		if (current->type == 0 || (current->type == 1 && current->tok[0] == '"'))
			if (ft_strrchr(current->tok, '$') == '$')
				ft_expand();
		current = current->next;
	}
}
