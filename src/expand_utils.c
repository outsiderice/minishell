/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/25 11:38:54 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find end of env variable name and return it's length
int	find_dollar_end(const char *name)
{
	int	i;

	i = 1;
	if (ft_isdigit(name[i]) == 1)
		return (3);
	while (name[i] && (ft_isalnum(name[i]) == 1 || name[i] == '_'))
		i++;
	i++;
	return (i);
}

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
	if (!str)
		return (NULL);
	return(str);
}
