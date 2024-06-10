/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 20:54:40 by amagnell         ###   ########.fr       */
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

	printf("inisde add_last\n");
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
	
	printf("inisde args node\n");
	new_arg = malloc(sizeof(t_args) * 1);
	if (!new_arg)
		return(-1);	//malloc protecc
	new_arg->argv = arr;
	new_arg->redir_fd = -1;
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
//Returns pointer to tokens
t_tokens	*fill_arg(t_args **args, t_tokens *tok)
{
	char		**arr;
	int			arr_len;
	int			i;


	printf("inisde fill arg\n");
	i = 0;
	arr_len = ft_count_toks(tok, 0);
	arr = malloc(sizeof(char *) * (arr_len + 1));
	if (!arr)
	{
		return (NULL); //add proper handling
	}
	arr[arr_len] = NULL;
	while (arr[i])
	{
		arr[i] = ft_strdup(tok->tok);
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

	printf("inisde prep args\n");
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
	printf("i want to print what's inside\n");
	int i = 0;
	if (args->next == NULL)
		printf("no more args\n");
	while (args->next != NULL)
	{
		ft_printf("in printing loop\n");
		while (args != NULL && args->argv[i] != NULL)
		{
			ft_printf("%s\n", args->argv[i]);
			i++;
		}
		args = args->next;
	}
	while (args != NULL && args->argv[i] != NULL)
	{
		ft_printf("%s\n", args->argv[i]);
		i++;
	}
	printf("end of prep args\n");
}
