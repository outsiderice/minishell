/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/28 15:37:40 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks that there's an acceptable token on both sides of a '|'
//if there isn't it gives an error and new line
void	ft_pipe_syntax(t_tokens *tok)
{
	if (tok->type == 2)
		printf("pipe syntax error\n");	//add proper error and nl
	tok = tok->next;
	if (tok->next == NULL || tok->next->type == 2)
		printf("pipe syntax error\n");	//add proper error and nl
}

//if the token next to a redirection is not a word (type 0) give an error and nl
void	ft_redir_syntax(t_tokens *tok)
{
	if (tok->next == NULL || (tok->next->type != 0 && tok->next->type != 1))
		printf("redir syntax error\n"); //add proper error and nl
}

//ft_parse checks:
//that there's tokens which are not '|' at both sides of a pipe
//that there's a word type token after a redirection << >> > <
//if the both are true it will go on to execution
void	ft_parse(t_ms *ms)
{
	t_tokens	*current;
	
	current = ms->tokens;
	while (current->next != NULL)
	{
		if (current->next->type == 2)
			ft_pipe_syntax(&current);
		if (current->type == 3)
			ft_redir_syntax(&current);
		current = current->next;
	}
}
