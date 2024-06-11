/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/11 11:42:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//opens the filename given by the input
//saves if it's input or output
// void	handle_redir()
// {}

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
		return(-1);	//malloc protecc
	new_arg->argv = arr;
	int i = 0;
	printf("argv[0] == %s\n", new_arg->argv[i]);
	new_arg->redir_fd = -1;
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

// static void	free_str(char **arr)
// {
// 	int	j;

// 	j = 0;
// 	while (arr[j])
// 	{
// 		free(arr[j]);
// 		j++;
// 	}
// 	free (arr);
// 	return ;
// }

//Fills array arr with consecutive tokens of the same type
//Returns pointer to tokens
t_tokens	*fill_arg(t_args **args, t_tokens *tok)
{
	char		**arr;
	int			arr_len;
	int			i;

	i = 0;
	arr_len = ft_count_toks(tok, 0);
	arr = malloc(sizeof(char *) * (arr_len + 1));
	if (!arr)
	{
		printf("FUCK\n");
		return (NULL); //add proper handling
	}
	arr[arr_len] = NULL;
	while (arr[i])
	{
		arr[i] = ft_strdup(tok->tok);
		printf("arr[i] = %s, tok is = %s\n", arr[i], tok->tok);
		tok = tok->next;
		i++;
	}
	new_args_node(args, arr);
	return (tok);
}

//Creates nodes for t_args from t_tokens
//when a '|' token is found it starts a new node
void	ft_prep_args(t_ms *ms)
{
	t_args		*args;
	t_tokens	*current_tok;

	current_tok = ms->tokens;
	args = NULL;
	while (current_tok != NULL)
	{
		while (current_tok && current_tok->type != 2)
		{
			if (current_tok->type == 0)
				fill_arg(&args, current_tok);
			current_tok = current_tok->next;
		}
	}
	int i = 0;
	while (args->next != NULL)
	{
		while (args != NULL && args->argv[i] != NULL)
		{
			ft_printf("\nStored in args:<%s>\n\n", args->argv[i]);
			i++;
		}
		args = args->next;
		printf("\n~On to next node~\n\n");
	}
	while (args != NULL && args->argv[i] != NULL)
	{
		ft_printf("\nStored in args node:<%s>\n\n", args->argv[i]);
		i++;
	}
}
