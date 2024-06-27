/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/27 15:22:46 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if it's a builtin and if it isn't calls execve
void	exeggutor(t_ms *ms)
{
	ft_prep_args(ms);
	//heredoc
	//check_files
	// if (handle_builtins() != -1)
	// 	printf("one full command executed\n");//free stuff and newline
	// else
	// 	printf("other exec\n")//execve();
	printf("1\n");
	ft_exec(ms);
}
