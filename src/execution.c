/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/10 13:09:29 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	exeggutor(t_ms *ms)
{
	ms->heredoc = handle_heredocs(ms);
	if (ft_prep_args(ms) == 0 && ms->args->argv != NULL)
	{
		if (ft_exec(ms, ms->args) == 1)
			ms->exitstatus = 1;
	}
	free_tok_and_args(&ms->tokens, &ms->args);
}
