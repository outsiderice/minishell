/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 17:23:34 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_parse checks:
//that there's tokens which are not '|' at both sides of a pipe
//that there's a word type token after a redirection << >> > <
//if it finds a $ it calls expansion
//if the first are both true it will go on to execution
void	ft_parse(t_ms *ms)
{
	t_tokens	*current;
	
	current = ms->tokens;
	while (current->next != NULL)
	{
		if (current->type == 2)
			ft_pipe_syntax();
		if (current->type == 3)
			ft_redir_syntax();
		current = current->next;
	}
}
