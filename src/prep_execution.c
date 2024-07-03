/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/03 11:26:49 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds nodes to ms and links them
void	create_args(t_ms *ms, t_args **head, t_args **arg)
{
	new_args_node(&ms->args);
	if (*head == NULL)
	{
		*head = ms->args;
		*arg = *head;
	}
	else
	{
		(*arg)->next = ms->args;
		ms->args->prev = *arg;
		*arg = ms->args;
	}
}

// Assigns redir_type and saves filename to t_args
int	prep_redir(t_tokens **tok, t_args *args)
{
	if ((*tok)->tok[0] == '<')
	{
		if (ft_strlen((*tok)->tok) == 1)
			args->redir_type = 1;
		else
			args->redir_type = 2;
	}
	else if ((*tok)->tok[0] == '>')
	{
		if (ft_strlen((*tok)->tok) == 1)
			args->redir_type = 3;
		else
			args->redir_type = 4;
	}
	else if ((*tok)->type == 1)
	{
		args->filename = ft_strdup((*tok)->tok);
		if (!args->filename)
			return (EXIT_FAILURE);
	}
	(*tok) = (*tok)->next;
	return(EXIT_SUCCESS);
}

// Fills array arr with consecutive tokens of the same type
// Returns the array
char	**fill_argv(t_tokens **tok, t_tokens *ptr)
{
	char		**arr;
	int			arr_len;
	int			i;

	*tok = ptr;
	i = 0;
	arr_len = ft_count_toks(*tok, 0);
	arr = malloc(sizeof(char *) * (arr_len + 1));
	if (!arr)
		return (NULL); //add proper handling
	arr[arr_len] = NULL;
	while (i < arr_len)
	{
		arr[i] = ft_strdup((*tok)->tok);
		(*tok) = (*tok)->next;
		i++;
	}
	return (arr);
}

void	prep_command(t_tokens **current_tok, t_ms **ms)
{
	char	**arr;

	arr = NULL;
	if ((*current_tok)->type == 3 || (*current_tok)->type == 1)
		prep_redir(current_tok, (*ms)->args);
	else if ((*current_tok)->type == 0)
		arr = fill_argv(current_tok, *current_tok);
	if (arr != NULL)
	{
		(*ms)->args->argv = arr;
		arr = NULL;
	}
}

//test function DELETE LATER
void	print_args(t_ms *ms) 
{
	t_args *current;

	current = ms->args;
	while (current != NULL)
	{
		// Print argv
		if (current->argv != NULL)
		{
			printf("\nArguments: ");
			for (int i = 0; current->argv[i] != NULL; i++)
			{
				printf("%s ", current->argv[i]);
			}
			printf("\n");
		}
		else
		{
			printf("Arguments: NULL\n");
		}

		// Print filename
		if (current->filename != NULL)
		{
			printf("Filename: %s\n", current->filename);
		}
		else
		{
			printf("Filename: NULL\n");
		}

		// Print redir_type
		printf("Redirection Type: %d\n", current->redir_type);

		// Move to the next node
		current = current->next;

		printf("\n"); // Separate each node's output for readability
	}
}

// Creates nodes for t_args from t_tokens
void	ft_prep_args(t_ms *ms)
{
	t_args		*head;
	t_args		*arg;
	t_tokens	*current_tok;
	
	current_tok = ms->tokens;
	head = NULL;
	arg = NULL;
	while (current_tok != NULL) 
	{
		create_args(ms, &head, &arg);
		while (current_tok && current_tok->type != 2)
			prep_command(&current_tok, &ms);
		if (current_tok != NULL && current_tok->type == 2)
		{
			current_tok = current_tok->next;
			ms->args = NULL;
		}
	}
	ms->args = head;
	print_args(ms); //delete later
}
