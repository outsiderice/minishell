/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:11 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/24 16:04:44 by kkoval           ###   ########.fr       */
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


//this function has to return some sort of value for control check purposes or not :)
int	handle_builtins(t_env *env_list, t_args *args_list) //probably has to be **args_list to free properly after use
{
	//possible exit_status variable
	if (args_list == NULL) // only stays here to check bad redirection
		printf("YOU SHALL NOT PASS TO BUILTINS, without builtin commans\n");
	if (!ft_strncmp(args_list->arg, "echo", 4) && ft_strlen(args_list->arg) == 4)
		return ft_echo(args_list->next); // we send the next arg with is either the extension or the string or nothing to print
	else if (!ft_strncmp(args_list->arg, "pwd", 3) && ft_strlen(args_list->arg) == 3)
		return (ft_pwd());
	else if (!ft_strncmp(args_list->arg, "cd", 2) && ft_strlen(args_list->arg) == 2)
		return (ft_cd(env_list, args_list));
	else if (!ft_strncmp(args_list->arg, "env", 3) && ft_strlen(args_list->arg) == 3)
		ft_env(env_list);
	else if (!ft_strncmp(args_list->arg, "export", 6) && ft_strlen(args_list->arg) == 6)
		ft_cd();
	else if (!ft_strncmp(args_list->arg, "unset", 5) && ft_strlen(args_list->arg) == 5)
		return (ft_unset(env_list, args_list)); //probably the &env_list
	else if (!ft_strncmp(args_list->arg, "exit", 4) && ft_strlen(args_list->arg) == 4)
		return (ft_exit()); // for now void, the final aim is to have all of allocated memory passed to the function
	else 
		return (-1) //for now, error handelling;
}


//free args
/*
ft_buliting(t_tokens **tokens)
{
    t_tokens *current;

    if (current->token ftstrncompare(echo) && strlen)
    ft_echo
    {
        *current


    }
}
*/
