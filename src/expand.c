/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/25 11:24:23 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*all_join(char *s1, char *s2, char *s3)
{
	char	*result;
	char	*aux;

	aux = ft_strjoin(s1, s2);
	if (!aux)
		return (NULL);
	result = ft_strjoin(aux, s3);
	free(aux);
	if (!result)
		return (NULL);
	return (result);
}

// creates new_tok out of content and the beginning and end of the old tok
// stores it to the tok
// returns i at the character after the last char of content
// or returns -1 if allocation fails
int	ft_retokenize(t_tokens *tok, int i, char *content)
{
	char	*start;
	char	*end;
	int		c_len;
	char	*new_tok;

	c_len = ft_strlen(content);
	start = ft_substr(tok->tok, 0, i);
	if (!start)
		return (-1);
	end = ft_substr(tok->tok, i + c_len, ft_strlen(tok->tok) - (i + c_len));
	if (!end)
		return (-1);
	new_tok = all_join(start, content, end);
	free(start);
	free(end);
	if (!new_tok)
		return (-1);
	return (i + c_len);
}

// gets the var name and looks for it in env
// returns the character after the last on of the expanded var
int	expand_dollar(t_ms *ms, t_tokens *tok, int i)
{
	char		*var_name;
	char		*start;
	char		*content;
	t_env		*env;

	env = ms->env;
	var_name = rm_delimiters(tok->tok, &i);
	if (!var_name)
		return (-1);
	while (env != NULL && ft_str_compare(env->v_name, var_name) != 0)
		env = env->next;
	if (!env)
	{
		content = ft_strdup("");
		if (!content)
			return (-1);
	}
	else
		content = env->v_cont;
	i = ft_retokenize(tok, i, content);
	free (content);
	if (i == -1)
		return (-1);
	return (i);
}

// checks if a '$' is expandable or not
// returns the token with all it's variables expanded
int	is_expandable_dollar(t_ms *ms, t_tokens *tok)
{
	int		i;
	
	i = 0;
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(&tok->tok[i], '\'');
		else if (tok->tok[i] == '$')
		{
			i = expand_dollar(ms, tok, i); //is passed **tok to change token inside returns i, it being the character after whatever was expanded
			if (tok->tok == NULL || i == -1)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

// // It removes paired quotes as it finds them and creates a new string
// // Returns the new string created NEW_TOK
// char	*expand_quotes(t_tokens *tok)
// {
// 	int		i;
// 	int		j;
// 	char	*new_tok;
// 	char	*aux;
	
// 	i = 0;
// 	j = 0;
// 	new_tok = NULL;
// 	while (tok->tok[i])
// 	{
// 		if (tok->tok[i] == '"' || tok->tok[i] == '\'')
// 		{
// 			if (new_tok == NULL)
// 				new_tok = ft_substr(tok->tok, 0, i);
// 			aux = rm_delimiters(tok->tok, i);
// 			new_tok = ft_strjoin(new_tok, aux);
// 			i = i + ft_strlen(aux) + 1;
// 			j = i;
// 			free(aux);
// 		}
// 		i++;
// 	}
// 	if (tok->tok[j] != '\0')
// 		new_tok = append_end(new_tok, tok->tok, j);
// 	return (new_tok);
// }

// It removes paired quotes as it finds them and creates a new string
// Returns the new string created NEW_TOK
int	expand_quotes(t_tokens *tok)
{
	int		i;
	char	*aux;
	
	i = 0;
	while (tok->tok[i])
	{
		if (ft_ismetachar(tok->tok[i]) == 1)
		{
			aux = rm_delimiters(tok->tok, &i);
			if (!aux)
				return (EXIT_FAILURE);
			i = ft_retokenize(tok, i, aux);
			free(aux);
			if (i == -1)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
