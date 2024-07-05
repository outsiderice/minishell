/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/05 02:40:54 by kate             ###   ########.fr       */
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

	args->fd[0] = STDIN_FILENO;
	args->fd[1] = STDOUT_FILENO;

    // Input redirection: '<'
	if (args->redir_type == 1)
	{
		args->fd[0] = open(args->filename, O_RDONLY);
		if (args->fd[0] == -1)
		{
			perror("open");
			exit(1);
		}
	}

    // Output redirection: '>'
    if (args->redir_type == 3) {
        args->fd[1] = open(args->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (args->fd[1] == -1) {
            perror("open");
            exit(1);
        }
    }

    // Append redirection: '>>'
    if (args->redir_type == 4) {
        args->fd[1] = open(args->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (args->fd[1] == -1) {
            perror("open");
            exit(1);
        }
    }

    // Here-doc redirection: '<<' (Implement if necessary)
    // You will need to handle here-doc separately, as it involves reading input until a delimiter.
}

int	handle_builtins(t_ms *ms, t_args *args) //probably has to be **msh to do exil propery and equal pointer to null
{
	printf("NO HA PEjkhgTADO\n");

    handle_redirections_builtin(args); //new
	printf("NO HA PETADO\n");
	if (ms->args == NULL) // only stays here to check bad redirection
		printf("YOU SHALL NOT PASS TO BUILTINS, without builtin commands\n");
	else if (ft_str_compare(args->argv[0], "echo") == 0)
		ms->exitstatus = ft_echo(args);
	else if (ft_str_compare(args->argv[0], "pwd") == 0)
		ms->exitstatus = ft_pwd();
	else if (ft_str_compare(ms->args->argv[0], "cd") == 0)
	 	ms->exitstatus = ft_cd(ms, ms->args->argv);
	else if (ft_str_compare(args->argv[0], "env") == 0)
		ms->exitstatus = ft_env(ms->env);
	else if (ft_str_compare(args->argv[0], "export") == 0)
		ms->exitstatus = ft_export(ms, args->argv); 
	else if (ft_str_compare(args->argv[0], "unset") == 0)
		ms->exitstatus = ft_unset(&ms->env, args->argv);
	else if (ft_str_compare(args->argv[0], "exit") == 0)
		ms->exitstatus = (ft_exit(args->argv)); // this should have access to the adress

	//if (args->redir_type != -1)    //new
    //handle_close(args); //new
	return (0);
}
