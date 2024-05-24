/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/24 15:58:59 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_init_gen

//starts readline loop
//starts signals loop
//inits gen struct
void	ft_minishell(char **env)
{
	char	*line;

	(void)env; //delete when env dealt with
	line = NULL;
	//init gen
	//copy to t-env env_list -- Kat
	while (2)
	{
		line = ft_readline();
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strlen(line) > 0)
			ft_check_input((const char *)line);
		free (line);
	}
	//start signals -	Kat
}

//passes env to minishell
int	main(int argc, char **argv, char **env)
{
	//char	**env_va;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_minishell(env);
	return (0);
}
