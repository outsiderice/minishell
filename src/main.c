/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/20 09:30:14 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_input.h"
#include "check_input.h"

void	ft_minishell(char **env)
{
	char	*line;

	(void)env;
	line = NULL;
	while (2)
	{
		line = ft_readline();
		ft_check_input((const char *)line);
		free (line);
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	**env_va;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_minishell(env);
	return (0);
}
