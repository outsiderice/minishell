/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/06 14:10:01 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	end = ft_substr(tok->tok, i + v, ft_strlen(tok->tok) - (i + v));
	if (!end)
		return (-1);
	if (c_len == 0)
		new_tok = ft_strjoin(start, end);
	else
		new_tok = all_join(start, content, end);
	free(start);
	free(end);
	if (!new_tok)
		return (-1);
	free(tok->tok);
	tok->tok = new_tok;
	return (i + c_len);
}

// gets the var name and looks for it in env
// returns updated i to the character after the last one of the expanded var
int	expand_dollar(t_ms *ms, t_tokens *tok, int i)
{
	char		*var_name;
	char		*content;
	t_env		*env;

	if (no_expansion(tok->tok, i) == 0)
		return (++i);
	env = ms->env;
	var_name = get_var_name(tok->tok, i);
	env = find_env_var(env, var_name);
	content = get_dollar_content(ms, env, var_name);
	if (!content)
	{
		free (var_name);
		return (-1);
	}
	i = ft_retokenize(tok, i, content, ft_strlen(var_name) + 1);
	free (var_name);
	free (content);
	return (i);
}

// checks if a '$' is in a expandable position or not
// returns 1 on failure and 0 on success
int	is_expandable_dollar(t_ms *ms, t_tokens *tok)
{
	int	i;
	int	in_qt;

	i = 0;
	in_qt = 0;
	while (tok->tok[i])
	{
		if (tok->tok[i] == '"')
		{
			in_qt++;
			if (in_qt == 2)
				in_qt = 0;
		}
		if (tok->tok[i] == '\'' && in_qt == 0)
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

//iterates TOK while tok[i] is not a quote
//adds all the characters found to string SHIT and returns it
char	*add_unquoted(char *tok, int i)
{
	char	*shit;
	int		shit_len;
	int		j;

	j = i;
	shit_len = 0;
	while (tok[i] && ft_ismetachar(tok[i]) == 0)
	{
		shit_len++;
		i++;
	}
	shit = ft_substr(tok, j, shit_len);
	if (!shit)
		return (NULL);
	return (shit);
}

// It removes paired quotes as it finds them and creates a new string
// Returns 1 on failure and 0 on success
int	expand_quotes(t_tokens *tok)
{
	int		i;
	char	*aux;

	i = 0;
	while (tok->tok[i])
	{
		if (ft_ismetachar(tok->tok[i]) == 1)
		{
			aux = rm_delimiters(tok->tok, i);
			if (!aux)
				return (EXIT_FAILURE);
			i = ft_retokenize(tok, i, aux, ft_strlen(aux) + 2);
		}
		else
		{
			aux = add_unquoted(tok->tok, i);
			if (!aux)
				return (EXIT_FAILURE);
			i = ft_retokenize(tok, i, aux, ft_strlen(aux));
		}
		free(aux);
		if (i == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
