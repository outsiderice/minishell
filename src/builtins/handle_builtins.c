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

// I think this it a necessary controler file that would call other builtin functions,
// as some of them need more arguments than others. So this one would receive all the possible arguments needed.
// As the structure is still not clear, we will see later how exactly we can hanfle it.
// So far I understand there is going to be a structure that would have inside the number or code name 
// to determinate if it should call builtin or command, in case of a built-in it would end here, and from here
// 1 of the 7 built-in functions would be called.
// Some of them require more arguments then others.
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
	char **b_args;

	b_args = ms->args->argv; 
	if (ms->args == NULL) // only stays here to check bad redirection
		printf("YOU SHALL NOT PASS TO BUILTINS, without builtin commands\n");


	else if (ft_str_compare(ms->args->argv[0], "echo") == 0)
		ms->exitstat = ft_echo(ms->args->argv[1]);


	else if (ft_str_compare(ms->args->argv[0], "pwd") == 0)
		ms->exitstat = ft_pwd();


	else if (ft_str_compare(ms->args->argv[0], "cd") == 0)
		ms->exitstat = ft_cd(ms, ms->args->argv[]); // to complete 


	else if (!ft_strncmp(ms->args->arg, "env", 3) && ft_strlen(ms->args->arg) == 3)
		ms->exitstat = ft_env(ms->env); //done, but needs checker


	else if (!ft_strncmp(ms->args->arg, "export", 6) && ft_strlen(ms->args->arg) == 6)
		ms->exitstat(ft_export()); 


	else if (!ft_strncmp(ms->args->arg, "unset", 5) && ft_strlen(ms->args->arg) == 5)
		ms->exitstat(ft_unset(ms->env, ms->args)); //probably the &env_list


	else if (!ft_strncmp(ms->args->arg, "exit", 4) && ft_strlen(ms->args->arg) == 4)
		ms->exitstat(ft_exit()); // for now void, the final aim is to have all of allocated memory passed to the function
	else 
		return (-1); //for now, error handelling;
}


/* TODO
	- free the first argument as we pass it to builtin? 
	- gestionar return y exitstatus
*/