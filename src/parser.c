/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:17:12 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/24 16:11:06 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find a redirection and check if there's a word after it
//if there's no word it's an error
void	ft_parse(t_tokens *tokens)
{
	while (tokens->next != NULL)
	{
		if (tokens->type == 2 && tokens->next->type == 2)
		{
			printf("error found near redirection\n");
			//new prompt line
		}
		else
			tokens = tokens->next;
	}
	//begins execution before redirection or the other way around?
	ft_execution();
}
