/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/20 09:36:12 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find end of env variable name and return it's length
int	find_dollar_end(const char *name)
{
	int	i;

	i = 1;
	if (ft_isdigit(name[i]) == 1)
		return (i);
	while (name[i] && (ft_isalnum(name[i]) == 1 || name[i] == '_'))
		i++;
	return (i);
}

// 	Removes the characters at both ends of TOK
char	*rm_delimiters(t_tokens *tok, int i)
{
	char	*str;
	int		len;


	if (ft_ismetachar(tok->tok[i]) == 1)
		len = ft_quote_len(&tok->tok[i], tok->tok[i]);
	else
		len = find_dollar_end();
	str = ft_substr(tok->tok, i + 1, len - 2);
	return(str);
}

//find the ending delimiter, create a substr of the part after the delimiter if needed, 
//find the env variable and make another string 
//use strjoin with the first part and then if needed the 3rd???
void	expand_dollar()
{
	
}

//checks if a '$' is expandable or not
//if it is calls a function to expand it
// int	is_expandable_dollar(t_tokens *tok)
// {
// 	int	i;

// 	i = 0;
// 	while(tok->tok[i])
// 	{
// 		if (tok->tok[i] == '\'')
// 			i = i + ft_quote_len(&tok->tok[i], '\'');
// 		if (tok->tok[i] == '$')
// 			expand_dollar(tok->tok, i); //find the ending delimiter, create a substr of the part after the delimiter if needed, find the env variable and make another string use strjoin with the first part and then if needed the 3rd???
// 	}
// }

// It removes paired quotes as it finds them and creates a new string
// Returns the new string created NEW_TOK
char	*expand_quotes(t_tokens *tok)
{
	int		i;
	char	*new_tok;
	char	*aux;
	
	i = 0;
	new_tok = NULL;
	while (tok->tok[i])
	{
		if (tok->tok[i] == '"' || tok->tok[i] == '\'')
		{
			if (new_tok == NULL)
				new_tok = ft_substr(tok->tok, 0, i);
			aux = rm_delimiters(tok, i);
			new_tok = ft_strjoin(new_tok, aux);
			i = i + ft_strlen(aux) + 1;
			free(aux);
		}
		i++;
	}
	return (new_tok);
}
