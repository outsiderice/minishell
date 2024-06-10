/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 12:23:22 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//opens the filename given by the input
//saves if it's input or output
// void	handle_redir()
// {}

//Creates and returns a t_args node
t_args	*add_args_node(char *aux, t_tokens *last_tok)
{
	t_args	*node;

	node = NULL;
	if (last_tok->type == 2)
		pipe(node->fd);
	//node->redir_fd = ; //change later
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
	
	printf("inside prep args\n");
	while (ms->tokens != NULL)
	{
		printf("while there are tokens\n");
		while (ms->tokens->type != 2)
		{
			printf("while the token is not a pipe\n");
			if (ms->tokens->type == 0 || ms->tokens->type == 1)
			{
				printf("the token is  a word\n");
				aux = ft_strjoin(ms->tokens->tok, ",");
				aux2 = ft_strjoin(aux2, aux);
				free(aux);
			}
			else if (ms->tokens->type == 3)
				printf ("calls handle_redir\n");//handle_redir();
			printf("dealt with this token, next token\n");
			ms->tokens = ms->tokens->next;
			printf("on next token\n");
		}
		ms->args = add_args_node(aux, ms->tokens);
		printf("returned new args node\n");
		ms->args = ms->args->next;
		ms->tokens = ms->tokens->next;
	}
	while (ms->args->argv)
	{
		printf("%s/n", *ms->args->argv);
		ms->args->argv++;
	}
	printf("end of prep args\n");
}
