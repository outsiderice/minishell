/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/09 18:26:56 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	signal_handler(int signal)
{
	int	mode;

	mode = 0;
	if (mode == 0 && signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}*/

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
	//ms->pid = getpid(); quizas no va aqui
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
	struct	sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	//sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	ft_init_ms(&ms, envp);
	ft_minishell(&ms);
	return (0);
}
