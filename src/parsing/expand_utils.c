/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/12 16:59:45 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for cases of no expansion
int	no_expansion(t_tokens *token, char *tok, int i)
{
	int		len;
	char	*content;

	content = NULL;
	len = 0;
	if (ft_ismetachar(tok[++i]) == 1)
	{
		if (tok[i] != tok[i + 1])
		{
			content = ft_strdup("");
			i--;
			i = ft_retokenize(token, i, content, 1);
			free(content);
			if (i == -1)
				return (-2);
			return (-1);
		}
		len = ft_quote_len(tok, tok[i]);
		if (len == 2)
			return (0);
	}
	if (ft_isalnum(tok[i]) == 0 && tok[i] != '_' && tok[i] != '?')
		return (1);
	return (0);
}

char	*get_dollar_content(t_ms *ms, t_env *env, char *var_name)
{
	char	*content;

	content = NULL;
	if (!env)
	{
		if (ft_str_compare(var_name, "?") == 0)
			content = ft_itoa(ms->exitstatus);
		else
			content = ft_strdup("");
	}
	else
		content = ft_strdup(env->v_cont);
	return (content);
}

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
// Returns STR or NULL if allocation failed
char	*rm_delimiters(char *tok, int i)
{
	char	*str;
	int		len;

	if (ft_ismetachar(tok[i]) == 1)
		len = ft_quote_len(&tok[i], tok[i]);
	else
	{
		len = find_dollar_end(&tok[i]);
		if (len == 2)
		{
			str = ft_strdup("$");
			return (str);
		}
	}
	str = ft_substr(tok, i + 1, len - 2);
	if (!str)
		return (NULL);
	return (str);
}

//joins three strings into RESULT which is returned
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
