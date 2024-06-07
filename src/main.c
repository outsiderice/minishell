/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/07 12:48:12 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{
	ms->env = NULL;
	ms->tokens = NULL;
	//ms->args = NULL;
	ms->exitstatus = -1;
	ms->sh_lvl = -1; //HOW?
	ms->old_pwd = NULL;
	ms->new_pwd = getcwd(NULL, 0);
	//if (ms->new_pwd == NULL) exit ("getcwd error")//protection for if new_pwd returns NULL?
	ms->pid = getpid();
}

//the minishell execution loop
//starts readline loop
//starts signals loop
void	ft_minishell(t_ms *ms)
{
	char	*line;

	line = NULL;
	while (2)
	{
		//start signals -	Kat
		line = ft_readline();
		if (ft_strlen(line) > 0)
		{
			if (ft_check_quotes((const char *)line) != 0)
				syntax_error();
			ft_tokenize(line, ms);
			ft_parse(ms);
			// ft_exeggutor();
		}
		free (line);
	}
}

//inits ms and env structs and stores envp
int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_init_ms(&ms);
	ms.env = start_env(envp);
	if (ms.env == NULL)
		return (EXIT_FAILURE);
	ft_minishell(&ms);
	return (0);
}
