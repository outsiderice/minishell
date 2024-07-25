/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/10 14:56:53 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if it's a builtin and if it isn't calls execve
void	exeggutor(t_ms *ms)
{
	if (ft_prep_args(ms) == 0) //needs proper handling once executor is cleaned up
	{
	//heredoc
	//check_files
	// if (handle_builtins() != -1)
	// 	printf("one full command executed\n");//free stuff and newline
	// else
	// 	printf("other exec\n")//execve();
	printf("about to enter exec\n");
	ft_exec(ms, ms->args);
	}
	free_tok_and_args(&ms->tokens, &ms->args);
}
