/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/28 11:28:32 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the $ which must be expanded
//look for the value and substiute for what's found in env 
//or an empty string if not found
//remove quotes

//find $ signs to be expanded in the tokens
//checks if a token is type 0-word or type 1-quoted and that the quotes are "
//	then looks for a dollar sign inside these specific tokens
//	when a dollar sign is found calls an expansion function
void	ft_expansion_check(t_ms *ms)
{
	
}