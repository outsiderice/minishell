/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:30:50 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/08 23:13:35 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Frees a string array
void	free_arr(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free (arr);
	return ;
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

// Creates new node for args
// Returns 1 if there's an allocation failure or 0 if it's a success
int	new_args_node(t_args **args)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args) * 1);
	if (!new_arg)
		return (EXIT_FAILURE);
	new_arg->argv = NULL;
	new_arg->fd[0] = -2; //-2; for pipes
	new_arg->fd[1] = -2; //-2; for pipes
	new_arg->redir_type = -1;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (*args == NULL)
		*args = new_arg;
	else
		add_last_arg(args, new_arg);
	return (EXIT_SUCCESS);
}

// Counts how many consecutive tokens of the same TYPE there are from CURRENT
// Returns COUNT
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
