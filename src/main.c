/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/08 12:40:33 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_ms *ms, char **envp)
{
	char buffer[1024];

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
	ms->pwd = getcwd(buffer, 1024);
	ms->old_pwd = getcwd(buffer, 1024);
	//printf("buffer: %s\n", buffer);
	if (ms->old_pwd == NULL || ms->pwd == NULL)
	{
		free_env(&ms->env);
		exit (error_msg("getcwd: Returned NULL\n", NULL));
	}
	ms->pid = NULL;
}

//the minishell execution loop
//starts readline loop
//starts signals loop
void	ft_minishell(t_ms *ms)
{
	char	*line;

	line = NULL;
	while (42)
	{
		ft_start_signals(1);
		ft_ignoresig(SIGQUIT);
		line = ft_readline(ms, "eggshell~$");
		// ms->exitstatus = g_signstat + 128;
		// if (g_signstat == 0)
		// 	ms->exitstatus = 0;
		// g_signstat = 0;
		while (line)
		{
			ft_start_signals(1);
			if (ft_tok_checks(line, ms) == 0 && ft_parse(ms) == 0)
				exeggutor(ms);
			free (line);
			line = NULL;
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
