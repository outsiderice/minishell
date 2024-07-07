/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/06 23:54:15 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_init_ms(t_ms *ms, char **envp)
{
	ms->env = start_env(envp);
	if (ms->env == NULL || ft_set_shll_lvl(ms->env) == -1)
	{
		free_env(&ms->env);
		return (exit (error_msg("env memory allocation failure\n", NULL)));
	}
	ms->tokens = NULL;
	ms->args = NULL;
	ms->exitstatus = -1;
	ms->sh_lvl = ft_get_shll_lvl(ms->env);
	ms->old_pwd = getcwd(NULL, 0);
	if (ms->old_pwd == NULL)
	{
		free_env(&ms->env);
		exit (error_msg("getcwd:Returned NULL old_pwd\n", NULL));
	}
	ms->pwd = getcwd(NULL, 0);
	if (ms->pwd == NULL)
	{
		free_env(&ms->env);
		exit (error_msg("getcwd:Returned NULL new_pwd\n", NULL));
	}
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
			if (ft_tok_checks(line, ms) == 0 && ft_parse(ms) == 0)
					exeggutor(ms);
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
	ft_minishell(&ms);
	return (0);
}
