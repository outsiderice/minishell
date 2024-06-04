/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/02 15:07:30 by amagnell         ###   ########.fr       */
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

void	ft_get_args(t_ms *ms)
{
	while (ms->tokens->type != 2)
	{
		//make arg_arr
		//if ms->tokens->type == 3
			//set_redir() get input and output fd
	}
}

//ft_parse checks:
//that there's tokens which are not '|' at both sides of a pipe
//that there's a word type token after a redirection << >> > <
//if the first two are true:
//it will check if there's anything to expand, get_args and then call execution
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
	//ft_expansion_check();
	// ft_get_args(ms);
	// exeggutor(ms);
}
