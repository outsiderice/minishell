/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/09 18:56:05 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if it's a builtin and if it isn't calls execve
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
