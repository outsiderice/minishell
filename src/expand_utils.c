/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/21 08:47:34 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removes the characters at both ends of TOK
char	*rm_delimiters(char *tok, int i)
{
	char	*str;
	int		len;

	if (ft_ismetachar(tok[i]) == 1)
		len = ft_quote_len(&tok[i], tok[i]);
	else
		len = find_dollar_end(&tok[i]);
	str = ft_substr(tok, i + 1, len - 2);
	return(str);
}
