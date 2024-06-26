/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/26 14:03:55 by amagnell         ###   ########.fr       */
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
	printf("stored start = <%s>\n", start);
	end = ft_substr(tok->tok, i + v, ft_strlen(tok->tok) - (i + v));
	if (!end)
		return (-1);
	printf("stored end = <%s>\n", end);
	if (c_len == 0)
		new_tok = ft_strjoin(start, end);
	else
		new_tok = all_join(start, content, end);
	printf("stored new_tok = <%s>\n", new_tok);
	free(start);
	free(end);
	if (!new_tok)
		return (-1);
	free(tok->tok);
	tok->tok = new_tok;
	printf("changed tok->tok = <%s>\n", tok->tok);
	return (i + c_len);
}

// gets the var name and looks for it in env
// returns the character after the last one of the expanded var
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
	printf("stored content = <%s>\n AND tok->tok[i] is %c\n", content, tok->tok[i]);
	i = ft_retokenize(tok, i, content, ft_strlen(var_name) + 1);
	printf("where are you?\n");
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
	int	i;
	int	in_qt;

	i = 0;
	in_qt = 0;
	printf("is it a expandable dollar?\n");
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
		printf("stuck in a while loop\n");
	}
	return (EXIT_SUCCESS);
}

//iterates TOK while tok[i] is not a quote
//adds all the characters found to string SHIT and returns it
char	*add_shit(char *tok, int i)
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
	printf("shit is %s\n", shit);
	return (shit);
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
			printf("stored aux = <%s>\n", aux);
			i = ft_retokenize(tok, i, aux, ft_strlen(aux) + 2);
			printf("[i] after retoken is %c\n", tok->tok[i]);
		}
		else
		{
			printf("tok->tok[i] is: %c\n", tok->tok[i]);
			aux = add_shit(tok->tok, i);
			printf("stored aux = <%s>\n", aux);
			if (!aux)
				return (EXIT_FAILURE);
			i = ft_retokenize(tok, i, aux, ft_strlen(aux));
		}
		if (i == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
