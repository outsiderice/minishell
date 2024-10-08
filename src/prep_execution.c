/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/11 18:14:21 by amagnell         ###   ########.fr       */
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

// Assigns redir type and opens fds as needed
int	prep_redir(t_ms *ms, t_tokens **tok, t_args *args)
{
	if ((*tok)->tok[0] == '<')
		open_input((*tok)->tok, (*tok)->next->tok, args, ms);
	else if ((*tok)->tok[0] == '>')
		open_output((*tok)->tok, (*tok)->next->tok, args);
	(*tok) = (*tok)->next;
	return (EXIT_SUCCESS);
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
		if ((*tok)->type == 0)
		{
			arr[i] = ft_strdup((*tok)->tok);
			if (!arr[i++])
			{
				free_arr(arr);
				return (NULL);
			}
		}
		(*tok) = (*tok)->next;
	}
	return (arr);
}

// Returns 1 on failure and 0 on success
int	prep_command(t_tokens **current_tok, t_ms **ms)
{
	char	**arr;
	int		done;

	arr = NULL;
	done = 0;
	if ((*current_tok)->type >= 3 || (*current_tok)->type == 1)
	{
		if (prep_redir((*ms), current_tok, (*ms)->args) == 1)
			return (EXIT_FAILURE);
	}
	else if ((*current_tok)->type == 0 && done == 0)
	{
		arr = fill_argv(current_tok, *current_tok);
		if (!arr)
			return (EXIT_FAILURE);
		done = 1;
	}
	if (arr != NULL)
	{
		(*ms)->args->argv = arr;
		arr = NULL;
	}
	return (EXIT_SUCCESS);
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
	ms->cmnds_num = ft_t_args_len(ms->args);
	return (EXIT_SUCCESS);
}
