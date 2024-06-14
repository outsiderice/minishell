/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/12 15:00:29 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms, char **envp)
{
	ms->env = start_env(envp);
	ms->tokens = NULL;
	ms->args = NULL;
	ms->exitstatus = -1;
	ms->sh_lvl = ft_shll_lvl(m->env);
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
	printf("eggshell go!\n");
	while (42)
	{
		printf("inside 42\n");
		//start signals -	Kat
		line = ft_readline();
		while (line)
		{
			printf("line!\n");
			if (ft_tokenize(line, ms) == 0)
			{
				ft_parse(ms);
				exeggutor(ms);
			}
			free (line);
			line = NULL;
			printf("~freed line~\n\n");
		}
	}
}

//inits ms and env structs and stores envp
int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_init_ms(&ms, envp);
	if (ms.env == NULL)
		return (EXIT_FAILURE);
	ft_minishell(&ms);
	return (0);
}
