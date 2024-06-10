/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/07 11:18:39 by amagnell         ###   ########.fr       */
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

typedef	struct s_ms
{
	t_env		*env;
	t_tokens	*tokens;
	t_args		*args;
	//t_pipes		*pipes;
	int			exitstatus;
	int			sh_lvl;
	char		*new_pwd;
	char		*old_pwd;
	int			pid;
}	t_ms;

typedef struct s_args
{
	int				input;
	int				output;
	int				argc;
	char			**argv;
	struct s_args	*next;
}	t_args;

//this function has to return some sort of value for control check purposes or not :)
int	handle_builtins(t_ms *ms) //probably has to be **msh to do exil propery and equal pointer to null
{
	if (ms->args == NULL) // only stays here to check bad redirection
		printf("YOU SHALL NOT PASS TO BUILTINS, without builtin commands\n");
	else if (ft_str_compare(ms->args->argv[0], "echo") == 0)
		ms->exitstatus = ft_echo(ms->args->argv);
	else if (ft_str_compare(ms->args->argv[0], "pwd") == 0)
		ms->exitstatus = ft_pwd(ms);
	else if (ft_str_compare(ms->args->argv[0], "cd") == 0)
		ms->exitstatus = ft_cd(ms, ms->args->argv); // to complete 
	else if (ft_str_compare(ms->args->argv[0], "env") == 0)
		ms->exitstatus = ft_env(ms->env);
	else if (ft_str_compare(ms->args->argv[0], "export") == 0)
		ms->exitstatus = ft_export(&ms, ms->args->argv); 
	else if (ft_str_compare(ms->args->argv[0], "unset") == 0)
		ms->exitstatus = ft_unset(&ms->env, ms->args->argv);
	else if (ft_str_compare(ms->args->argv[0], "exit") == 0)
		ms->exitstatus = (ft_exit(&ms)); // this should have access to the adress
	else 
		return (-1); // means that it is not a builtin
}
