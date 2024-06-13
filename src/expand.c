/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/13 16:20:48 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the $ which must be expanded
//look for the value and substitute for what's found in env 
//or an empty string if not found
//remove quotes

//
int	is_expandable_dollar(t_tokens *tok)
{
	int	i;

	i = 0;
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(tok->tok, '\'');
		if (tok->tok[i] == '$')
			expand_dollar(tok->tok, i); //find the ending delimiter, create a substr of the part after the delimiter if needed, find the env variable and make another string use strjoin with the first part and then if needed the 3rd???
	}
}
