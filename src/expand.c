/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/25 12:22:56 by amagnell         ###   ########.fr       */
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
int	ft_retokenize(t_tokens *tok, int i, char *content, int v)
{
	char	*start;
	char	*end;
	int		c_len;
	char	*new_tok;

	c_len = ft_strlen(content);
	start = ft_substr(tok->tok, 0, i);
	if (!start)
		return (-1);
	printf("stored start = <%s>\n", start);
	end = ft_substr(tok->tok, i + v + 1, ft_strlen(tok->tok) - (i + v));
	if (!end)
		return (-1);
	printf("stored end = <%s>\n", end);
	new_tok = all_join(start, content, end);
	printf("stored new_tok = <%s>\n", new_tok);
	free(start);
	free(end);
	if (!new_tok)
		return (-1);
	free(tok->tok);
	tok->tok = new_tok;
	printf("changed tok->tok = <%s>\n", tok->tok);
	return (i + c_len + 1);
}

// gets the var name and looks for it in env
// returns the character after the last on of the expanded var
int	expand_dollar(t_ms *ms, t_tokens *tok, int i)
{
	char		*var_name;
	char		*content;
	t_env		*env;

	env = ms->env;
	var_name = rm_delimiters(tok->tok, i);
	if (!var_name)
		return (-1);
	printf("stored var_name = <%s>\n", var_name);
	while (env != NULL && ft_str_compare(env->v_name, var_name) != 0)
		env = env->next;
	if (!env)
		content = ft_strdup("");
	else
		content = ft_strdup(env->v_cont);
	if (!content)
	{
		free (var_name);
		return (-1);
	}
	printf("stored content = <%s>\n", content);
	i = ft_retokenize(tok, i, content, ft_strlen(var_name));
	free (var_name);
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
	printf("is it a expandable dollar?\n");
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(&tok->tok[i], '\'');
		else if (tok->tok[i] == '$')
		{
			i = expand_dollar(ms, tok, i);
			if (i == -1)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

// It removes paired quotes as it finds them and creates a new string
// Returns the new string created NEW_TOK
int	expand_quotes(t_tokens *tok)
{
	int		i;
	char	*aux;
	
	i = 0;
	printf("there are quotes to expand\n");
	while (tok->tok[i])
	{
		if (ft_ismetachar(tok->tok[i]) == 1)
		{
			aux = rm_delimiters(tok->tok, i);
			if (!aux)
				return (EXIT_FAILURE);
			i = ft_retokenize(tok, i, aux, ft_strlen(aux) + 2);
			free(aux);
			if (i == -1)
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
