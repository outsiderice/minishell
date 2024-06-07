/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/06 17:17:20 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{

	ms->env = NULL;
	ms->tokens = NULL;
	//ms->args = NULL;
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
		if (ft_strlen(line) > 0)
		{
			ft_check_quotes((const char *)line);
			ft_tokenize(line, ms);
		}
		free (line);
	}
	//start signals -	Kat
}

//passes env to minishell
int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_init_ms(&ms);
	ms.env = start_env(envp);
	ft_minishell(&ms);
	return (0);
}
