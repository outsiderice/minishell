/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 12:20:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks that there's an acceptable token on both sides of a '|'
//if there isn't it gives an error and new line
int	ft_pipe_syntax(t_tokens *tok)
{
	if (tok->type == 2)
	{
		printf("pipe syntax error\n");
		exit(1) ;
	}	//add proper error and nl
	if (tok->next)
		tok = tok->next;
	if (tok->next == NULL || tok->next->type == 2)
	{
		printf("pipe syntax error\n");	//add proper error and nl
		exit(1) ;
	}
	return (0);
}

//if the token next to a redirection is not a type 0 (word) give an error and nl
//if the following token is type 0 changes it's type from 0 to 1 (filename)
void	ft_redir_syntax(t_tokens *tok)
{
	if (tok->next == NULL || (tok->next->type != 0 && tok->next->type != 1))
		printf("redir syntax error\n"); //add proper error and nl
	else
		tok->next->type = 1;
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
	while (current != NULL)
	{
		printf("in parse loop \n");
		if (current->type == 2 || (current->next && current->next->type == 2))
			ft_pipe_syntax(current);
		if (current->type == 3)
			ft_redir_syntax(current);
		printf("next node please\n");
		current = current->next;
	}
	printf("end of parse\n");
	//ft_expansion_check();
}
