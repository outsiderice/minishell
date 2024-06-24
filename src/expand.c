/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:37:06 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/21 18:39:50 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ok, so expansion it does stuff brrrrr
we've come to the conclusion that dollars should be expanded before quotes, is that right?
Yes. next.
fuck complex tokens. anyway lets reason this out once more:
-in the case of "hello"
easy peasy just remove the delimiting quotes
-in the case of 'hi'bye */


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

// gets the var name and looks for it in env
// returns the content of the var if found or and empty string if not
char	*expand_dollar(t_ms *ms, t_tokens *tok, int *i, int j)
{
	char	*var_name;
	char	*content;
	t_env	*env;

	env = ms->env;
	var_name = rm_delimiters(tok->tok, &j);
	*i = j + ft_strlen(var_name) + 1;
	while (env != NULL && ft_str_compare(env->v_name, var_name) != 0)
		env = env->next;
	if (!env)
		return (ft_strdup(""));
	content = env->v_cont;
	return (content);
}

// expands the variable and substitutes the var name with it
//returns the token with the expanded $
char	*ft_retokenize(t_ms *ms, t_tokens *tok, int *i, int j)
{
	char	*new_tok;
	char	*start;
	char	*aux;
	char	*end;
	
	start = ft_substr(tok->tok, 0, j);
	aux = expand_dollar(ms, tok, &j, j);
	end = ft_substr(tok->tok, j, ft_strlen(tok->tok) - j);
	new_tok = ft_strjoin(start, aux);
	free(aux);
	aux = ft_strjoin(new_tok, end);
	free(start);
	free(new_tok);
	free(end);
	*i = j;
	return (aux);
}

// checks if a '$' is expandable or not
// if it is calls ft_retokenizeS
// returns the token with all it's expanded vars
char	*is_expandable_dollar(t_ms *ms, t_tokens *tok)
{
	int		i;
	char	*new_tok;
	
	i = 0;
	new_tok = NULL;
	while(tok->tok[i])
	{
		if (tok->tok[i] == '\'')
			i = i + ft_quote_len(&tok->tok[i], '\'');
		if (tok->tok[i] == '$')
		{
			if (new_tok == NULL)
				new_tok = ft_retokenize(ms, tok, &i, i);
			else
				new_tok = ft_retokenize(ms, tok, &i, i);
		}
		i++;
	}
	if (new_tok == NULL)
		return (ft_strdup(tok->tok));
	return (new_tok);
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
char	*expand_quotes(t_tokens *tok)
{
	int		i;
	char	*new_tok;
	char	*aux;
	
	i = 0;
	new_tok = NULL;
	while (tok->tok[i])
	{
		if (ft_ismetachar(tok->tok[i]) == 1)
		{
			if (new_tok == NULL)
				new_tok = ft_substr(tok->tok, 0, i);
			aux = rm_delimiters(tok->tok, &i);
			new_tok = ft_strjoin(new_tok, aux);
			printf("i is %d char is %c\n", i, tok->tok[i]);
			free(aux);
		}
		else
			new_tok = add_shit(new_tok, &tok->tok[i], &i);
		printf("new_tok = %s\n", new_tok);
	}
	return (new_tok);
}
