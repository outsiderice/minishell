/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 09:43:18 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//opens the filename given by the input
//saves if it's input or output
// void	handle_redir()
// {}

t_args	*add_args_node(char *aux)
{
	t_args	*node;

	(void)node->fd; //change later
	node->redir_fd = NULL; //change later
	node->argv = ft_split(aux, ',');
	free(aux);
	node->next = NULL;
	return (node);
}

//Creates nodes for s_args
//Fills current node argv until it finds a '|' or NULL.
//if it finds a redirection calls ft_handle_redirs
void	ft_prep_args(t_ms *ms)
{
	char		*aux;
	char		*aux2;
	
	while (ms->tokens != NULL)
	{
		while (ms->tokens->type != 2)
		{
			if (ms->tokens->type == 0 || ms->tokens->type == 1)
			{
				aux = ft_strjoin(ms->tokens->tok, ",");
				aux2 = ft_strjoin(aux2, aux);
				free(aux);
			}
			else if (ms->tokens->type == 3)
				printf ("calls handle_redir\n");//handle_redir();
			ms->tokens = ms->tokens->next;
		}
		ms->args = add_args_node(aux);
		ms->args = ms->args->next;
		ms->tokens = ms->tokens->next;
	}
}
