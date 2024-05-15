/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/15 15:30:26 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = "eggshell~$";
	line = readline(prompt);
	if (!line)
		exit(EXIT_FAILURE);
	return (line);
}

void	ft_minishell(char **env)
{
	(void)env;
	char	*line;

	line = NULL;
	while (2)
	{
		line = ft_readline();
		free (line);
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_minishell(env);
	return (0);
}
