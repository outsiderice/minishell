/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/14 19:29:42 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the ending delimiter, create a substr of the part after the delimiter if needed, 
//find the env variable and make another string 
//use strjoin with the first part and then if needed the 3rd???
void	expand_dollar()
{
	
}

//checks if a '$' is expandable or not
//if it is calls a function to expand it
int	is_expandable_dollar(t_tokens *tok)
{
	int	i;

	i = 0;
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(&tok->tok[i], '\'');
		if (tok->tok[i] == '$')
			expand_dollar(tok->tok, i); //find the ending delimiter, create a substr of the part after the delimiter if needed, find the env variable and make another string use strjoin with the first part and then if needed the 3rd???
	}
}

// iterates token, when it finds a quote it finds the ending pair and removes both
void	expand_quotes(t_tokens *tok)
{
	int		i;
	int		len;
	char	*start;
	char	*end;
	char	*update;

	i = 0;
	len = 0;
	while (tok->tok[i])
	{
		if (tok->tok[i] == '"' || tok->tok[i] == '\'')
		{
			len = ft_quote_len(&tok->tok[i], tok->tok[i]);
			start = ft_substr(tok->tok, 0, i);
			end = ft_substr(tok->tok, i + 1, len - 2);
			update = ft_strjoin(start, end);
			free(start);
			free(end);
			end = ft_substr(tok->tok, i + len, ft_strlen(tok->tok) - (i + len));
			start = ft_strjoin(update, end);
			free(update);
			free(end);
		}
		i++;
	}
	free(tok->tok);
	tok->tok = start;
	free(start);
}
