/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:26:40 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 12:16:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if it's a builtin and if it isn't calls execve
void	exeggutor(t_ms *ms)
{
	ft_prep_args(ms);
	// if (handle_builtins() != -1)
	// 	printf("one full command executed\n");//free stuff and newline
	// else
	// 	printf("other exec\n")//execve();
}
