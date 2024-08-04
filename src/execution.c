/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/04 14:48:47 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if it's a builtin and if it isn't calls execve
void	exeggutor(t_ms *ms)
{
	ms->heredoc = handle_heredocs(ms);
	if (ft_prep_args(ms) == 0 && ms->args->argv != NULL) //needs proper handling once executor is cleaned up
	{
		//printf("about to enter exec\n");
		ft_exec(ms, ms->args);
	}
	free_tok_and_args(&ms->tokens, &ms->args);
}
