/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/04 15:56:09 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* THINGS TO CONSIDER:
	1. when to free the args. Built-in final function? 
	If so, then pass ms->args->argv instead of ms->args->argv[1]
	2. Should builtins be case incensitive? Bash accepts pwd, PWD, pwD etc..
*/

// 0 success, 1 unexplained fail 2 missuse of shell commands
//Case incensitive will accept pwd, PWD, pwD etc..

//this function has to return some sort of value for control check purposes or not :)

int	is_builtin(char *cmd)
{
	if ((ft_str_compare(cmd, "echo") == 0) || (ft_str_compare(cmd, "pwd") == 0) ||
		(ft_str_compare(cmd, "cd") == 0) || (ft_str_compare(cmd, "env") == 0) ||
		(ft_str_compare(cmd, "export") == 0) || (ft_str_compare(cmd, "unset") == 0) ||
		(ft_str_compare(cmd, "exit") == 0))
		return (1);
	return (0);
}

void	handle_redirections_builtin(t_args *args) 
{
    // Input redirection: '<'
    if (args->fd[0] != -1 && args->fd[0] != -2)
    {
        if (dup2(args->fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(args->fd[0]);
    }

    // Output redirection: '>' and '>>'
    if (args->fd[1] != -1 && args->fd[1] != -2) {
        if (dup2(args->fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(args->fd[1]);
    }
}

int	handle_builtins(t_ms *ms, t_args *args, int fd) //probably has to be **msh to do exil propery and equal pointer to null
{
	if (ft_str_compare(args->argv[0], "echo") == 0)
		return (ft_echo(args, fd));
	else if (ft_str_compare(args->argv[0], "pwd") == 0)
		return (ft_pwd(fd));
	else if (ft_str_compare(ms->args->argv[0], "cd") == 0)
	 	return (ft_cd(ms, ms->args->argv));
	else if (ft_str_compare(args->argv[0], "env") == 0)
		return (ft_env(ms->env, fd));
	else if (ft_str_compare(args->argv[0], "export") == 0)
		return (ft_export(ms, args->argv, fd)); 
	else if (ft_str_compare(args->argv[0], "unset") == 0)
		return (ft_unset(ms, args->argv));
	else if (ft_str_compare(args->argv[0], "exit") == 0)
		return (ft_exit(ms, args->argv)); // this should have access to the adress
	return (-1);
}
