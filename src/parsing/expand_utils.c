/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:42:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/04 14:37:12 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dollar_content(t_ms *ms, t_env *env, char *var_name)
{
	char	*content;

	content = NULL;
	if (!env)
	{
		if (ft_str_compare(var_name, "$?") == 0)
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
		len = find_dollar_end(&tok[i]);
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
