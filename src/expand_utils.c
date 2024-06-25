/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/25 09:43:06 by amagnell         ###   ########.fr       */
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
char	*rm_delimiters(char *tok, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	if (ft_ismetachar(tok[j]) == 1)
		len = ft_quote_len(&tok[j], tok[j]);
	else
		len = find_dollar_end(&tok[j]);
	str = ft_substr(tok, j + 1, len - 2);
	*i = j + len;
	return(str);
}

//
char	*append_end(char *start, char *original, int i)
{
	char	*new_tok;
	char	*aux;

	i++;
	aux = ft_substr(original, i, ft_strlen(original) - i);
	new_tok = ft_strjoin(start, aux);
	free(aux);
	return (new_tok);
}

//adds shit to the new_tok
char	*add_shit(char	*str, char *src, int *ptr)
{
	int		start;
	int		end;
	char	*shit;
	char	*new_tok;

	start = *ptr;
	end = start;
	while (ft_ismetachar(src[end]) != 1)
		end++;
	shit = ft_substr(src, start, end - start);
	*ptr = end;
	if (!str)
		return (shit);
	new_tok = ft_strjoin(str, shit);
	free(str);
	free(shit);
	return (new_tok);
}
