/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/24 12:53:20 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms)
{
	ms->env = NULL;
	ms->tokens = NULL;
	ms->args = NULL;
	ms->exitstatus = -1;
	ms->sh_lvl = -1; //HOW?
	ms->old_pwd = NULL;
	ms->new_pwd = getcwd(NULL, 0);
	if (ms->new_pwd == NULL)
		exit (error_msg("getcwd:Returned NULL new_pwd\n", NULL));
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
		//start signals -	Kat
		line = ft_readline();
		while (line)
		{
			printf("line!\n");
			if (ft_tok_checks(line, ms) == 0)
			{
				if (ft_parse(ms) == 0)
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
	ft_init_ms(&ms);
	ms.env = start_env(envp);
	if (ms.env == NULL)
	{
		//function which frees ms and env
		return (error_msg("env memory allocation failure\n", NULL));
	}
	ft_minishell(&ms);
	return (0);
}
