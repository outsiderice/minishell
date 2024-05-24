/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/24 16:41:20 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms, t_env *envlst)
{

	ms->env = envlst;
	ms->tokens = NULL;
	//ms->args = NULL;
	//ms->pipes = NULL;
	ms->exec_value = -1;
	ms->sh_lvl = -1; //HOW?
	ms->old_pwd = NULL;
	ms->new_pwd = getcwd(NULL, 0);
	ms->pid = getpid();
}

//starts readline loop
//starts signals loop
//inits gen struct
void	ft_minishell(t_ms *ms)
{
	char	*line;

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
	//start signals -	Kat
}

//passes env to minishell
int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	//ft_init_env;
	ft_init_ms(&ms, env);
	ft_minishell(&ms);
	return (0);
}
