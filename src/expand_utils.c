/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/20 17:42:52 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removes the characters at both ends of TOK
char	*rm_delimiters(t_tokens *tok, int i)
{
	char	*str;
	int		len;

	if (ft_ismetachar(tok->tok[i]) == 1)
		len = ft_quote_len(&tok->tok[i], tok->tok[i]);
	else
		len = find_dollar_end(&tok->tok[i]);
	str = ft_substr(tok->tok, i + 1, len - 2);
	return(str);
}
