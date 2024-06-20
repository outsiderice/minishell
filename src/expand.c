/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/20 16:28:23 by amagnell         ###   ########.fr       */
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
char	*rm_delimiters(t_tokens *tok, int i)
{
	char	*str;
	int		len;

	if (ft_ismetachar(tok->tok[i]) == 1)
		len = ft_quote_len(&tok->tok[i], tok->tok[i]);
	else
		len = find_dollar_end(&tok->tok[i]);
	str = ft_substr(tok->tok, i + 1, len - 2);
	printf("str is %s\n", str);
	return(str);
}

// gets the var name and looks for it in env
// returns the content of the var if found or and empty string if not
char	*expand_dollar(t_ms *ms, t_tokens *tok, int *i, int j)
{
	char	*var_name;
	char	*content;
	t_env	*env;

	env = ms->env;
	var_name = rm_delimiters(tok, j);
	printf("var name is %s\n", var_name);
	*i = j + ft_strlen(var_name) + 1;
	while (env != NULL && ft_str_compare(env->v_name, var_name) != 0)
		env = env->next;
	if (!env)
		return (ft_strdup(""));
	content = env->v_cont;
	return (content);
}

// checks if a '$' is expandable or not
// if it is calls a function to expand it
// returns the token with all it's expanded vars
char	*is_expandable_dollar(t_ms *ms, t_tokens *tok)
{
	int		i;
	char	*new_tok;
	char	*aux;
	
	i = 0;
	new_tok = NULL;
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(&tok->tok[i], '\'');
		if (tok->tok[i] == '$')
		{
			if (new_tok == NULL)
				new_tok = ft_substr(tok->tok, 0, i);
			aux = expand_dollar(ms, tok, &i, i);
			new_tok = ft_strjoin(new_tok, aux);
			free(aux);
		}
		i++;
	}
	return (new_tok);
}

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
