/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/02 15:53:19 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Counts how many consecutive tokens of the same TYPE there are from CURRENT
//Returns COUNT
int	ft_count_toks(t_tokens *current, int type)
{
	int	count;

	count = 0;
	while (current && current->type == type)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// Adds node to the end of the args list
void	add_last_arg(t_args **args, t_args *new_arg)
{
	t_args	*last;

	last = *args;
	while (last && last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_arg;
	new_arg->prev = last;
}

//Creates new node for args
int	new_args_node(t_args **args)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args) * 1);
	if (!new_arg)
		return (-1);	//malloc protecc
	new_arg->argv = NULL;
	new_arg->filename = NULL;
	new_arg->redir_type = -1;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (*args == NULL)
		*args = new_arg;
	else
		add_last_arg(args, new_arg);
	return (0);
}

//Fills array arr with consecutive tokens of the same type
//Returns the array
char	**fill_arg(t_tokens **tok, t_tokens *ptr)
{
	char		**arr;
	int			arr_len;
	int			i;

	*tok = ptr;
	i = 0;
	arr_len = ft_count_toks(*tok, 0);
	arr = malloc(sizeof(char *) * (arr_len + 1));
	if (!arr)
	{
		printf("bad malloc\n");
		return (NULL); //add proper handling
	}
	arr[arr_len] = NULL;
	printf("before while to fill array\n");
	while (i < arr_len)
	{
		arr[i] = ft_strdup((*tok)->tok);
		printf("arr[%d] = %s, tok is = %s\n", i, arr[i], (*tok)->tok);
		(*tok) = (*tok)->next;
		i++;
	}
	printf("end of fill\n");
	return (arr);
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

// void	create_args(t_ms *ms, t_args *head, t_args *arg)
// {
// 	new_args_node(&ms->args);
// 	if (head == NULL)
// 	{
// 		head = ms->args;
// 		arg = head;
// 	}
// 	else
// 	{
// 		arg->next = ms->args;
// 		ms->args->prev = arg;
// 		arg = ms->args;
// 	}
// }

void	prep_command(t_tokens **current_tok, t_ms **ms)
{
	char	**arr;

	arr = NULL;
	if ((*current_tok)->type == 3 || (*current_tok)->type == 1)
		prep_redir(current_tok, (*ms)->args);
	else if ((*current_tok)->type == 0)
		arr = fill_arg(current_tok, *current_tok);
	if (arr != NULL)
	{
		(*ms)->args->argv = arr;
		arr = NULL;
	}
}

//Creates nodes for t_args from t_tokens
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
		new_args_node(&ms->args);
		if (head == NULL)
		{
			head = ms->args;
			arg = head;
		}
		else
		{
			arg->next = ms->args;
			ms->args->prev = arg;
			arg = ms->args;
		}
		while (current_tok && current_tok->type != 2)
			prep_command(&current_tok, &ms);
		if (current_tok != NULL && current_tok->type == 2)
		{
			current_tok = current_tok->next;
			ms->args = NULL;
		}
	}
	ms->args = head;
	print_args(ms);
}
