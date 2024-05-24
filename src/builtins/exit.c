/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:44 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/24 16:04:10 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Cntol C and exit can be the same?????
	function to free the minishell struct
	function to free the t_env list
	call the function to free the t_arg list
	function to exit status
*/

//provisional function to test handle_builtins
int	ft_exit(void) //should receive all possible structures to free them and possibly save the readline history
{
	printf("you reached exit builtin, have a nice day :D \n");
	return (1);
}