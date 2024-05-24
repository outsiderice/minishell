/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:59:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/24 16:03:01 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_newpromptline?

//shows prompt and returns user input
//adds history
char	*ft_readline(void)
{
	char		*line;
	const char	*prompt;

	prompt = "eggshell~$";
	line = readline(prompt);
	if (!line)
		exit(EXIT_FAILURE);
	if (line)
		add_history(line);
	return (line);
}
