/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:59:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/09 17:39:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_newpromptline?

//shows prompt and returns user input
//adds history
char	*ft_readline(t_ms *ms)
{
	char		*line;
	const char	*prompt;

	prompt = "eggshell~$";
	line = readline(prompt);
	if (!line)
	{
		free_env(&ms->env);
		printf("exit\n");
		exit(0);
	}
	if (line)
		add_history(line);
	return (line);
}
