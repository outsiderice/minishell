/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:58:32 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/16 18:17:04 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exec_cmd(t_ms *ms, char **args, t_env *env)
{
	char	*cmd;
	char	*path;
	char	**paths;

	cmd = args[0];
	paths = ft_get_paths(env);
	path = ft_find_path(cmd, paths);
	if (path != NULL)
		cmd = ft_join_path(path, cmd);
	ms->envp = ft_list_to_array(env);
	if (execve(cmd, args, ms->envp) == -1)
	{
		error_msg2("eggshell: ", cmd, ": No such file or directory", 1);
		free_arr(ms->envp);
		free_arr(paths);
		free(path);
		exit (127);
	}
	free(path);
	free_arr(paths);
	return (0);
}

void	ft_exec_child(t_ms *ms, t_args *args, int i)
{
	if (args->fd[0] != -2)
	{
		if (args->redir_type == 2 || check_access(ms, args->i_file) == 0)
			dup2(args->fd[0], STDIN_FILENO);
		else
			return ;
	}
	else if (i != 0)
		dup2(ms->pipes[i - 1][0], STDIN_FILENO);
	if (args->fd[1] != -2)
	{
		if (check_access(ms, args->o_file) == 0)
			dup2(args->fd[1], STDOUT_FILENO);
		else
			return ;
	}
	else if (i != ms->cmnds_num - 1)
		dup2(ms->pipes[i][1], STDOUT_FILENO);
	if (ms->cmnds_num > 1)
		close_pipes(ms->pipes, 0, ms->cmnds_num, ms->cmnds_num - 1);
	ft_close_fd(ms->args);
	ms->exitstatus = ft_exec_cmd(ms, args->argv, ms->env);
	return ;
}

void	ft_exec_builtin(t_ms *ms, t_args *args, int i)
{
	int	out_fd;

	out_fd = 1;
	if (args->fd[1] != -2)
	{
		if (check_access(ms, args->o_file) == 0)
			out_fd = args->fd[1];
		else
			return ;
	}
	else if (i != ms->cmnds_num -1)
		out_fd = ms->pipes[i][1];
	ms->exitstatus = handle_builtins(ms, args, out_fd);
	return ;
}

void	create_forks(t_ms *ms, t_args *args, int i)
{
	ms->pid[i] = fork();
	if (ms->pid[i] == 0)
	{
		if (is_builtin(args->argv[0]) == 1)
		{
			ft_exec_builtin(ms, args, i);
		}
		else
			ft_exec_child(ms, args, i);
		exit (ms->exitstatus);
	}
	else
	{
		ft_ignoresig(SIGINT);
		ft_ignoresig(SIGQUIT);
	}
}
