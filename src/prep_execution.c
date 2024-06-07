/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/06 12:04:15 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//opens the filename given by the input
//saves if it's input or output
void	handle_redir()
{}

//Creates nodes for s_args
//Fills current node argv until it finds a '|' or NULL.
//if it finds a redirection calls ft_handle_redirs
void	ft_prep_args(t_ms *ms)
{
	t_tokens	*current;
	int			i;
	int			str_count;

	i = 0;
	str_count = 0;
	while (ms->tokens != NULL)
	{
		current = ms->tokens;
		while (current->type != 2)
		{
			if (current->type == 0 || current->type == 1)
				str_count++;
			if (current->type == 3)
				handle_redir();
			current = current->next;
		}
		ft_fill_arr(ms,&ms->tokens, str_count);
		ms->tokens = ms->tokens->next;
	}
}
