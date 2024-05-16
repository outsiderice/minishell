/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:59:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 10:19:02 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include <stdlib.h>


char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = "eggshell~$";
	line = readline(prompt);
	if (!line)
		exit(EXIT_FAILURE);
	if (line)
		add_history(line);
	return (line);
}