/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:25:54 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/04 15:45:29 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable to change exitstatus
int	g_signstat;

/*
MISSING
-^\ message doesnt say (core dumped)
does core dumped imply anything else?
heredoc signals:
- ^c quits heredoc and gives a new promptline
- ^\ does nothing
- ^d gives a warning and gives a new promptline
*/

void	sig_handler(int signal)
{
	g_signstat = signal;
	if (signal == SIGINT) //exitstatus = 130
	{
		write(1, "\n", 1);
		//rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT) //exitstatus = 131
	{
		write(1, "Quit\n", 5);
	}
}

void	heredoc_sigmode(int signal)
{
	if (signal == SIGINT)
		exit(130);
}

void	ft_ignoresig(int signal)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signal, &sa, NULL) == -1)
	{
		perror("sigaction\n");
		exit(EXIT_FAILURE);
	}
}

void    ft_start_signals(int mode)
{
    struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 1)
		sa.sa_handler = sig_handler;
	else if (mode == 2)
	 	sa.sa_handler = heredoc_sigmode;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
