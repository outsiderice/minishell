/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/10 19:04:56 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_args(t_ms *ms, t_args *args)
{
	int	i;
	
	i = 0;
	while (i < ms->cmnds_num)
	{
		if (i != ms->cmnds_num - 1 && pipe(ms->pipes[i]) == -1)
			return (1);
		if (ms->cmnds_num == 1 && is_builtin(args->argv[0]) == 1)
			ft_exec_builtin(ms, args, i);
		else
			create_forks(ms, args, i);
		args = args->next;
		i++;
	}
	close_pipes(ms->pipes, 0, ms->cmnds_num, ms->cmnds_num - 1);
	return (0);
}

int	ft_exec(t_ms *ms, t_args *args)
{	    
	int	stat;
	int	i;

	i = 0;
	if (handle_pipes(ms) == -1 || handle_pids(ms) == -1)
	{
		error_msg("allocation failure", NULL);
		return (1);
	}
	if (ft_exec_args(ms, args) == 1)
		return (1);
	if (is_builtin(args->argv[0]) == 0 || ms->cmnds_num != 1)
	{
		while (i < ms->cmnds_num)
		{
			waitpid(ms->pid[i], &stat, 0);
			ms->exitstatus = WEXITSTATUS(stat);
			i++;
		}
	}
	return (0);
}

void	exeggutor(t_ms *ms)
{
	ms->heredoc = handle_heredocs(ms);
	if (ft_prep_args(ms) == 0 && ms->args->argv != NULL)
	{
		if (ft_exec(ms, ms->args) == 1)
			ms->exitstatus = 1;
	}
	if (ms->pid != NULL)
		free_int_ptr(ms->pid);
	ft_close_fd(ms->args);
	free_tok_and_args(&ms->tokens, &ms->args);
}
