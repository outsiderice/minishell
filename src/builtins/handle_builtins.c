/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/03 15:00:33 by kkoval           ###   ########.fr       */
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

#include <fcntl.h>
#include <unistd.h>

void handle_redirections_builtin(t_args *args) 
{
    int fd;

    // Input redirection: '<'
    if (args->redir_type == 1) {
        fd = open(args->filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    }

    // Output redirection: '>'
    if (args->redir_type == 3) {
        fd = open(args->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    }

    // Append redirection: '>>'
    if (args->redir_type == 4) {
        fd = open(args->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    }

    // Here-doc redirection: '<<' (Implement if necessary)
    // You will need to handle here-doc separately, as it involves reading input until a delimiter.
}


int	handle_builtins(t_ms *ms, t_args *args) //probably has to be **msh to do exil propery and equal pointer to null
{
	if (args->redir_type != -1)    //new
        handle_redirections_builtin(args); //new

	if (ms->args == NULL) // only stays here to check bad redirection
		printf("YOU SHALL NOT PASS TO BUILTINS, without builtin commands\n");
	else if (ft_str_compare(args->argv[0], "echo") == 0)
		ms->exitstatus = ft_echo(args->argv);
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
	else 
		return (-1); // means that it is not a builtin
	return (0);
}
