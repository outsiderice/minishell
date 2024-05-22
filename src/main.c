/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 09:35:50 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_input.h"
#include "check_input.h"
#include "../lib/libft/include/libft.h"

void	ft_minishell(char **env)
{
	char	*line;

	(void)env;
	line = NULL;
	while (2)
	{
		line = ft_readline();
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strlen(line) > 0)
			ft_check_input((const char *)line);
		free (line);
	}
}

int	main(int argc, char **argv, char **env)
{
	//char	**env_va;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_minishell(env);
	return (0);
}
