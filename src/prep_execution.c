/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/19 12:19:18 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds nodes to ms and links them
// Returns 1 on failure and 0 on success
int	create_args(t_ms *ms, t_args **head, t_args **arg)
{
	if (new_args_node(&ms->args))
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

// Assigns redir_type and saves filename to t_args
int	prep_redir(t_tokens **tok, t_args *args)
{
	if ((*tok)->tok[0] == '<')
	{
		if (ft_strlen((*tok)->tok) == 1)
		{
			args->fd[0] = open((*tok)->next->tok, O_RDONLY);
			args->redir_type = 1;
		}
		else
		{
			//maybe dup heredocfd?
			args->redir_type = 2;
		}
	}
	else if ((*tok)->tok[0] == '>')
	{
		if (ft_strlen((*tok)->tok) == 1)
		{
			args->fd[1] = open((*tok)->next->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			args->redir_type = 3;
		}
		else
		{
			args->fd[1] = open((*tok)->next->tok, O_WRONLY | O_CREAT | O_APPEND, 0644);
			args->redir_type = 4;
		}
	}
	(*tok) = (*tok)->next;
	return(EXIT_SUCCESS);
}

// Fills array arr with consecutive tokens of the same type
// Returns the array or NULL if it fails
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
		return (NULL);
	arr[arr_len] = NULL;
	while (i < arr_len)
	{
		arr[i] = ft_strdup((*tok)->tok);
		if (!arr[i])
		{
			free_arr(arr);
			return (NULL);
		}
		(*tok) = (*tok)->next;
		i++;
	}
	return (arr);
}

// Returns 1 on failure and 0 on success
int	prep_command(t_tokens **current_tok, t_ms **ms)
{
	char	**arr;

	arr = NULL;
	if ((*current_tok)->type >= 3 || (*current_tok)->type == 1)
	{
		if (prep_redir(current_tok, (*ms)->args) == 1) //needs to iterate for heredoc
		return (EXIT_FAILURE);
	}
	else if ((*current_tok)->type == 0)
	{
		arr = fill_argv(current_tok, *current_tok);
		if (!arr)
			return (EXIT_FAILURE);
	}
	if (arr != NULL)
	{
		(*ms)->args->argv = arr;
		arr = NULL;
	}
	printf("end of prep command\n");
	return (EXIT_SUCCESS);
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

		// Print redir_type
		printf("Redirection Type: %d\n", current->redir_type);

		// Move to the next node
		current = current->next;

		printf("\n"); // Separate each node's output for readability
	}
}

// predefine el primer y el ultimo fd si no hay redirecciones
void handler_fst_lst_redir(t_args *args)
{
	if (args == NULL)
		return;
	if (args->fd[0] == -2)
		args->fd[0] = STDIN_FILENO;
	while (args->next != NULL)
		args = args->next;
	if (args->fd[1] == -2)
		args->fd[1] = STDOUT_FILENO;
	return;
}

// Creates nodes for t_args from t_tokens
int	ft_prep_args(t_ms *ms)
{
	t_args		*head;
	t_args		*arg;
	t_tokens	*current_tok;
	
	current_tok = ms->tokens;
	head = NULL;
	arg = NULL;
	while (current_tok != NULL) 
	{
		if (create_args(ms, &head, &arg) == 1)
			return (EXIT_FAILURE);
		while (current_tok && current_tok->type != 2)
		{
			if (prep_command(&current_tok, &ms) == 1)
				return (EXIT_FAILURE);
		}
		if (current_tok != NULL && current_tok->type == 2)
		{
			current_tok = current_tok->next;
			ms->args = NULL;
		}
	}
	
	
	ms->args = head;
	// Kate: predefiniendo el fd del primero y ultimo arg
	handler_fst_lst_redir(ms->args);
	print_args(ms); //delete later
	return (EXIT_SUCCESS);
}
