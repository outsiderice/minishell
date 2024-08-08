/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/08 16:56:58 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks that there's an acceptable token on both sides of a '|'
//if there isn't it prints an error message and returns 1, else it returns 0
int	ft_pipe_syntax(t_tokens *tok, t_tokens *first_tok)
{
	if (first_tok->type == 2)
	{
		error_msg("syntax error near unexpected token,", tok->tok);
		free_toks(&first_tok);
		return (EXIT_FAILURE);
	}
	if (tok->next == NULL || tok->next->type == 2)
	{
		free_toks(&first_tok);
		error_msg("syntax error near unexpected token,", tok->tok);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//if the token next to a redirection is not a type 0 (word) returns 1
//if the following token is type 0 changes it's type from 0 to 1 (filename)
//if succesful returns 0
int	ft_redir_syntax(t_tokens *tok)
{
	if (tok->next == NULL || (tok->next->type != 0 && tok->next->type != 1))
	{
		error_msg("syntax error near unexpected token,", tok->tok);
		free_toks(&tok);
		return (EXIT_FAILURE);
	}
	else if (ft_str_compare(tok->tok, "<<") == 0)
	{
		tok->type = 4;
		tok->next->type = 5;
	}
	else
		tok->next->type = 1;
	return (EXIT_SUCCESS);
}

// Ft_expansion_check:
// iterates tokens to find things to expand
// if it finds a $ call a ft to check if they should be expanded
// if it finds a quote it calls the funciton to expand them
// returns 1 
int	ft_expansion_check(t_ms *ms)
{
	t_tokens	*tok;

	tok = ms->tokens;
	while (tok != NULL)
	{
		if ((tok->type == 0 || tok->type == 1) && ft_strchr(tok->tok, '$'))
		{
			if (is_expandable_dollar(ms, tok) == 1)
				return (EXIT_FAILURE);
		}
		if (tok->type != 5 \
		&& (ft_strchr(tok->tok, '\'') || ft_strchr(tok->tok, '"')))
		{
			if (expand_quotes(tok) == 1)
				return (EXIT_FAILURE);
		}
		tok = tok->next;
	}
	return (EXIT_SUCCESS);
}

//ft_parse checks:
//that there's tokens which are not '|' at both sides of a pipe
//that there's a word type token after a redirection << >> > <
//if the first two are true:
//it will check if there's anything to expand
int	ft_parse(t_ms *ms)
{
	t_tokens	*current;
	t_tokens	*first;

	first = ms->tokens;
	current = ms->tokens;
	while (current != NULL)
	{
		if (current->type == 2)
			if (ft_pipe_syntax(current, first) == 1)
				return (EXIT_FAILURE);
		if (current->type == 3)
			if (ft_redir_syntax(current) == 1)
				return (EXIT_FAILURE);
		current = current->next;
	}
	if (ft_expansion_check(ms) == 1)
	{
		error_msg("expansion memory allocation failure\n", NULL);
		free_toks(&first);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
