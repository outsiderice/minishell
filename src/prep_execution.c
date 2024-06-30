/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/30 17:57:57 by kkoval           ###   ########.fr       */
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
int	new_args_node(t_args **args, char **arr)
{
	t_args	*new_arg;
	t_args	*last;

	new_arg = malloc(sizeof(t_args) * 1);
	if (!new_arg)
		return (-1);	//malloc protecc
	new_arg->argv = arr;
	new_arg->filename = NULL;
	new_arg->redir_type = -1;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (*args == NULL)
		*args = new_arg;
	else
	{
		last = *args;
		while (last && last->next != NULL)
			last = last->next;
		new_arg->prev = last;
		last->next = new_arg;
	}
		// add_last_arg(args, new_arg);
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

//Creates nodes for t_args from t_tokens
void	ft_prep_args(t_ms *ms)
{
	t_args		*args;
	t_tokens	*current_tok;
	char		**arr;
	
	current_tok = ms->tokens;
	args = NULL;
	while (current_tok != NULL) 
	{
		new_args_node(&args, NULL);
		ms->args = args;
		printf("made new args node\n");
		while (current_tok && current_tok->type != 2) //while not finding a pipe
		{
			if (current_tok->type == 3 || current_tok->type == 1)
			{
				prep_redir(&current_tok, args);
				printf("\nfilename = %s\nredir type %d\n\n", args->filename, args->redir_type);
			}
			else if (current_tok->type == 0)
			{
				arr = fill_arg(&current_tok, current_tok);
				printf("filled arr\n");
			}
			if (arr)
			{
				args->argv = arr;
				printf("set arr to args->argv[0] = %s\n", args->argv[0]);
				//free_arr(arr);
				arr = NULL;
				printf("freed and set arr to null\n");
			}
			printf("end of pipe while\n");
		}
		if (current_tok != NULL && current_tok->type == 2)
		{
			printf("found a pipe\n");

			args = args->next;
			printf("args set to next which should be NULL\n");
			current_tok = current_tok->next;
		}
	}
	// Test to print what's in args structure
	args = ms->args;
	int	argcount = 1;
	while (args != NULL)
	{
		printf("args number %d\n", argcount);
		int i = 0;
		while (args->argv != NULL && args->argv[i] != NULL)
		{
			printf("\nStored in args:<%s>\n\n", args->argv[i]);
			i++;
		}
		argcount++;
		args = args->next;
		printf("\n~On to next node~\n\n");
	}
	// End of test delete later
}
